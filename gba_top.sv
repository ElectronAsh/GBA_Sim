/* gba_top.sv
 *
 *  Top module for the Game Boy Advance.
 *
 *  Team N64
 */

`include "gba_core_defines.vh"
`include "gba_mmio_defines.vh"
`default_nettype none

module gba_top (
	input  logic reset,

	input logic gba_clk,
	input logic clk_100,
	input logic clk_256,
	input logic vga_clk,
	
    input  logic [7:0] SW,
	
    input  logic JA1,
    output logic JA2, JA3,
    output logic [7:0] LD,
    
	output logic [3:0] VGA_R, VGA_G, VGA_B,
    output logic VGA_VS, VGA_HS,
	
	/*
    output logic AC_ADR0, AC_ADR1, AC_GPIO0, AC_MCLK, AC_SCK,
    input  logic AC_GPIO1, AC_GPIO2, AC_GPIO3,
    inout  wire  AC_SDA,
	*/
	
	output logic [15:0] AUD_L,
	output logic [15:0] AUD_R,
	output logic AUD_VALID,
	
	output logic [31:0] bus_mem_addr,	// Bytewise?
	
	output logic bus_system_read,
	input logic [31:0] bus_system_rdata,
	
	output logic bus_game_read,
	input logic [31:0] bus_game_rdata,
	
	output logic bus_io_reg_read,
	
	output logic bus_write,
	output logic [31:0] bus_wdata
);

    // 16.776 MHz clock for GBA/memory system
	/*
    logic gba_clk, clk_100, clk_256, vga_clk;

    clk_wiz_0 clk0 (.clk_in1(gba_clk),
                    .gba_clk, .clk_100, .clk_256, .vga_clk);
	*/

    // Buttons register output
    logic [15:0] buttons;

    // CPU
    logic  [4:0] mode;
    (* mark_debug = "true" *) logic        nIRQ;
    logic        abort;
    logic        cpu_preemptable;

    // Interrupt signals
    logic [15:0] reg_IF, reg_IE, reg_ACK;
    logic        timer0, timer1, timer2, timer3;

    // DMA
    (* mark_debug = "true" *) logic        dmaActive;
    logic        dma0, dma1, dma2, dma3;
    logic  [3:0] disable_dma;
    logic        sound_req1, sound_req2;

    // Timer
    (* mark_debug = "true" *) logic [15:0] internal_TM0CNT_L;
    logic [15:0] internal_TM1CNT_L;
    logic [15:0] internal_TM2CNT_L;
    logic [15:0] internal_TM3CNT_L;
    logic [15:0] TM0CNT_L, TM1CNT_L, TM2CNT_L, TM3CNT_L;

    // Memory signals
    (* mark_debug = "true" *) logic [31:0] bus_addr;
	//(* mark_debug = "true" *) logic [31:0] bus_wdata;
	(* mark_debug = "true" *) logic [31:0] bus_rdata;
    (* mark_debug = "true" *) logic  [1:0] bus_size;
    (* mark_debug = "true" *) logic        bus_pause;
	//(* mark_debug = "true" *) logic        bus_write;
    logic [31:0] gfx_vram_A_addr, gfx_vram_B_addr, gfx_vram_C_addr;
    logic [31:0] gfx_vram_A_addr2, gfx_palette_bg_addr;
    logic [31:0] gfx_oam_addr, gfx_palette_obj_addr;
    logic [31:0] gfx_vram_A_data, gfx_vram_B_data, gfx_vram_C_data;
    logic [31:0] gfx_vram_A_data2, gfx_palette_bg_data;
    logic [31:0] gfx_oam_data, gfx_palette_obj_data;

    logic        FIFO_re_A, FIFO_re_B, FIFO_clr_A, FIFO_clr_B;
    logic [31:0] FIFO_val_A, FIFO_val_B;
    logic  [3:0] FIFO_size_A, FIFO_size_B;
    
    logic  vblank, hblank, vcount_match;
    assign vblank = (vcount >= 8'd160);
    assign hblank = (hcount >= 9'd240);
    assign vcount_match = (vcount == DISPSTAT_REG[15:8]);

    //logic [31:0] IO_reg_datas [`NUM_IO_REGS-1:0];

    logic        dsASqRst, dsBSqRst;

    // Graphics
    logic [7:0] vcount;
    logic [8:0] hcount;

    assign abort = 1'b0;

    // CPU
    cpu_top cpu (.clock(gba_clk), .reset(reset), .nIRQ, .pause(bus_pause),
                 .abort, .mode, .preemptable(cpu_preemptable),
                 .dmaActive, .rdata(bus_rdata), .addr(bus_addr),
                 .wdata(bus_wdata), .size(bus_size), .write(bus_write));

    interrupt_controller intc
        (.clock(gba_clk), .reset(reset), .cpu_mode(mode), .nIRQ,
         .ime(IME_REG[0]),
         .reg_IE(IE_REG[15:0]),
         .set_vcount(DISPSTAT_REG[15:8]),
		 .vcount, .hcount,
		 .reg_IF, .reg_ACK,
         .timer0, .timer1,
         .timer2, .timer3, .serial(1'b0), .keypad(1'b0),
         .game_pak(1'b0), .dma0, .dma1, .dma2, .dma3);

    // BRAM memory controller
    mem_top mem (.clock(gba_clk), .reset(reset), .bus_addr, .bus_wdata, .bus_rdata,
                 .bus_size, .bus_pause, .bus_write, .dmaActive,

                 .gfx_vram_A_addr, .gfx_vram_B_addr, .gfx_vram_C_addr,
                 .gfx_palette_obj_addr, .gfx_palette_bg_addr,
                 .gfx_vram_A_addr2, .gfx_oam_addr,

                 .gfx_vram_A_data, .gfx_vram_B_data, .gfx_vram_C_data,
                 .gfx_palette_obj_data, .gfx_palette_bg_data,
                 .gfx_vram_A_data2, .gfx_oam_data,

                 //.IO_reg_datas,
				 
				.DISPCNT_REG(DISPCNT_REG),
				.DISPSTAT_REG(DISPSTAT_REG),
				.VCOUNT_REG(VCOUNT_REG),
				.BG0CNT_REG(BG0CNT_REG),
				.BG1CNT_REG(BG1CNT_REG),
				.BG2CNT_REG(BG2CNT_REG),
				.BG3CNT_REG(BG3CNT_REG),

				.BG0HOFS_REG(BG0HOFS_REG),
				.BG0VOFS_REG(BG0VOFS_REG),
				.BG1HOFS_REG(BG1HOFS_REG),
				.BG1VOFS_REG(BG1VOFS_REG),
				.BG2HOFS_REG(BG2HOFS_REG),
				.BG2VOFS_REG(BG2VOFS_REG),
				.BG3HOFS_REG(BG3HOFS_REG),
				.BG3VOFS_REG(BG3VOFS_REG),

				.BG2PA_REG(BG2PA_REG),
				.BG2PB_REG(BG2PB_REG),
				.BG2PC_REG(BG2PC_REG),
				.BG2PD_REG(BG2PD_REG),
				.BG2X_L_REG(BG2X_L_REG),
				.BG2X_H_REG(BG2X_H_REG),
				.BG2Y_L_REG(BG2Y_L_REG),
				.BG2Y_H_REG(BG2Y_H_REG),

				.BG3PA_REG(BG3PA_REG),
				.BG3PB_REG(BG3PB_REG),
				.BG3PC_REG(BG3PC_REG),
				.BG3PD_REG(BG3PD_REG),
				.BG3X_L_REG(BG3X_L_REG),
				.BG3X_H_REG(BG3X_H_REG),
				.BG3Y_L_REG(BG3Y_L_REG),
				.BG3Y_H_REG(BG3Y_H_REG),

				.WIN0H_REG(WIN0H_REG),
				.WIN1H_REG(WIN1H_REG),
				.WIN0V_REG(WIN0V_REG),
				.WIN1V_REG(WIN1V_REG),
				.WININ_REG(WININ_REG),
				.WINOUT_REG(WINOUT_REG),
				.MOSAIC_REG(MOSAIC_REG),

				.BLDCNT_REG(BLDCNT_REG),
				.BLDALPHA_REG(BLDALPHA_REG),
				.BLDY_REG(BLDY_REG),

				.SOUND1CNT_L_REG(SOUND1CNT_L_REG),
				.SOUND1CNT_H_REG(SOUND1CNT_H_REG),
				.SOUND1CNT_X_REG(SOUND1CNT_X_REG),
				.SOUND2CNT_L_REG(SOUND2CNT_L_REG),
				.SOUND2CNT_H_REG(SOUND2CNT_H_REG),
				.SOUND3CNT_L_REG(SOUND3CNT_L_REG),
				.SOUND3CNT_H_REG(SOUND3CNT_H_REG),
				.SOUND3CNT_X_REG(SOUND3CNT_X_REG),
				.SOUND4CNT_L_REG(SOUND4CNT_L_REG),
				.SOUND4CNT_H_REG(SOUND4CNT_H_REG),
				.SOUNDCNT_L_REG(SOUNDCNT_L_REG),
				.SOUNDCNT_H_REG(SOUNDCNT_H_REG),
				.SOUNDCNT_X_REG(SOUNDCNT_X_REG),
				.SOUNDBIAS_REG(SOUNDBIAS_REG),
				.WAVE_RAM0_L_REG(WAVE_RAM0_L_REG),
				.WAVE_RAM0_H_REG(WAVE_RAM0_H_REG),
				.WAVE_RAM1_L_REG(WAVE_RAM1_L_REG),
				.WAVE_RAM1_H_REG(WAVE_RAM1_H_REG),
				.WAVE_RAM2_L_REG(WAVE_RAM2_L_REG),
				.WAVE_RAM2_H_REG(WAVE_RAM2_H_REG),
				.WAVE_RAM3_L_REG(WAVE_RAM3_L_REG),
				.WAVE_RAM3_H_REG(WAVE_RAM3_H_REG),
				.FIFO_A_L_REG(FIFO_A_L_REG),
				.FIFO_A_H_REG(FIFO_A_H_REG),
				.FIFO_B_L_REG(FIFO_B_L_REG),
				.FIFO_B_H_REG(FIFO_B_H_REG),

				.DMA0SAD_L_REG(DMA0SAD_L_REG),
				.DMA0SAD_H_REG(DMA0SAD_H_REG),
				.DMA0DAD_L_REG(DMA0DAD_L_REG),
				.DMA0DAD_H_REG(DMA0DAD_H_REG),
				.DMA0CNT_L_REG(DMA0CNT_L_REG),
				.DMA0CNT_H_REG(DMA0CNT_H_REG),
				.DMA1SAD_L_REG(DMA1SAD_L_REG),
				.DMA1SAD_H_REG(DMA1SAD_H_REG),
				.DMA1DAD_L_REG(DMA1DAD_L_REG),
				.DMA1DAD_H_REG(DMA1DAD_H_REG),
				.DMA1CNT_L_REG(DMA1CNT_L_REG),
				.DMA1CNT_H_REG(DMA1CNT_H_REG),
				.DMA2SAD_L_REG(DMA2SAD_L_REG),
				.DMA2SAD_H_REG(DMA2SAD_H_REG),
				.DMA2DAD_L_REG(DMA2DAD_L_REG),
				.DMA2DAD_H_REG(DMA2DAD_H_REG),
				.DMA2CNT_L_REG(DMA2CNT_L_REG),
				.DMA2CNT_H_REG(DMA2CNT_H_REG),
				.DMA3SAD_L_REG(DMA3SAD_L_REG),
				.DMA3SAD_H_REG(DMA3SAD_H_REG),
				.DMA3DAD_L_REG(DMA3DAD_L_REG),
				.DMA3DAD_H_REG(DMA3DAD_H_REG),
				.DMA3CNT_L_REG(DMA3CNT_L_REG),
				.DMA3CNT_H_REG(DMA3CNT_H_REG),

				.TM0CNT_L_REG(TM0CNT_L_REG),
				.TM0CNT_H_REG(TM0CNT_H_REG),
				.TM1CNT_L_REG(TM1CNT_L_REG),
				.TM1CNT_H_REG(TM1CNT_H_REG),
				.TM2CNT_L_REG(TM2CNT_L_REG),
				.TM2CNT_H_REG(TM2CNT_H_REG),
				.TM3CNT_L_REG(TM3CNT_L_REG),
				.TM3CNT_H_REG(TM3CNT_H_REG),

				.SIODATA32_L_REG(SIODATA32_L_REG),
				.SIODATA32_H_REG(SIODATA32_H_REG),
				.SIOCNT_REG(SIOCNT_REG),
				.SIODATA8_REG(SIODATA8_REG),

				.SIOMULTI0_REG(SIOMULTI0_REG),
				.SIOMULTI1_REG(SIOMULTI1_REG),
				.SIOMULTI2_REG(SIOMULTI2_REG),
				.SIOMULTI3_REG(SIOMULTI3_REG),
				.SIOMLT_SEND_REG(SIOMLT_SEND_REG),

				.KEYINPUT_REG(KEYINPUT_REG),
				.KEYCNT_REG(KEYCNT_REG),

				.RCNT_REG(RCNT_REG),
				.JOYCNT_REG(JOYCNT_REG),
				.JOY_RECV_L_REG(JOY_RECV_L_REG),
				.JOY_RECV_H_REG(JOY_RECV_H_REG),
				.JOY_TRANS_L_REG(JOY_TRANS_L_REG),
				.JOY_TRANS_H_REG(JOY_TRANS_H_REG),
				.JOYSTAT_REG(JOYSTAT_REG),

				.IE_REG(IE_REG),
				.IF_REG(IF_REG),
				.WAITCNT_REG(WAITCNT_REG),
				.IME_REG(IME_REG),

				.LED_REG0_REG(LED_REG0),
				.LED_REG1_REG(LED_REG1),
				.LED_REG2_REG(LED_REG2),
				.LED_REG3_REG(LED_REG3),

                 .buttons, .vcount,
                 .reg_IF, .int_acks(reg_ACK),
                 .internal_TM0CNT_L, .internal_TM1CNT_L, .internal_TM2CNT_L,
                 .internal_TM3CNT_L,
                 .TM0CNT_L, .TM1CNT_L, .TM2CNT_L, .TM3CNT_L, .dsASqRst, .dsBSqRst,

                 .FIFO_re_A, .FIFO_re_B, .FIFO_clr_A, .FIFO_clr_B, .FIFO_val_A,
                 .FIFO_val_B, .FIFO_size_A, .FIFO_size_B,
                 .vblank, .hblank, .vcount_match,
				 
				.bus_mem_addr( bus_mem_addr ),
				
				.bus_system_read( bus_system_read ),
				.bus_system_rdata( bus_system_rdata ),
				
				.bus_game_read( bus_game_read ),
				.bus_game_rdata( bus_game_rdata ),
				
				.bus_io_reg_read( bus_io_reg_read )
				);

logic [31:0] DISPCNT_REG;
logic [31:0] DISPSTAT_REG;
logic [31:0] VCOUNT_REG;
logic [31:0] BG0CNT_REG;
logic [31:0] BG1CNT_REG;
logic [31:0] BG2CNT_REG;
logic [31:0] BG3CNT_REG;

logic [31:0] BG0HOFS_REG;
logic [31:0] BG0VOFS_REG;
logic [31:0] BG1HOFS_REG;
logic [31:0] BG1VOFS_REG;
logic [31:0] BG2HOFS_REG;
logic [31:0] BG2VOFS_REG;
logic [31:0] BG3HOFS_REG;
logic [31:0] BG3VOFS_REG;

logic [31:0] BG2PA_REG;
logic [31:0] BG2PB_REG;
logic [31:0] BG2PC_REG;
logic [31:0] BG2PD_REG;
logic [31:0] BG2X_L_REG;
logic [31:0] BG2X_H_REG;
logic [31:0] BG2Y_L_REG;
logic [31:0] BG2Y_H_REG;

logic [31:0] BG3PA_REG;
logic [31:0] BG3PB_REG;
logic [31:0] BG3PC_REG;
logic [31:0] BG3PD_REG;
logic [31:0] BG3X_L_REG;
logic [31:0] BG3X_H_REG;
logic [31:0] BG3Y_L_REG;
logic [31:0] BG3Y_H_REG;

logic [31:0] WIN0H_REG;
logic [31:0] WIN1H_REG;
logic [31:0] WIN0V_REG;
logic [31:0] WIN1V_REG;
logic [31:0] WININ_REG;
logic [31:0] WINOUT_REG;
logic [31:0] MOSAIC_REG;

logic [31:0] BLDCNT_REG;
logic [31:0] BLDALPHA_REG;
logic [31:0] BLDY_REG;

logic [31:0] SOUND1CNT_L_REG;
logic [31:0] SOUND1CNT_H_REG;
logic [31:0] SOUND1CNT_X_REG;
logic [31:0] SOUND2CNT_L_REG;
logic [31:0] SOUND2CNT_H_REG;
logic [31:0] SOUND3CNT_L_REG;
logic [31:0] SOUND3CNT_H_REG;
logic [31:0] SOUND3CNT_X_REG;
logic [31:0] SOUND4CNT_L_REG;
logic [31:0] SOUND4CNT_H_REG;
logic [31:0] SOUNDCNT_L_REG;
logic [31:0] SOUNDCNT_H_REG;
logic [31:0] SOUNDCNT_X_REG;
logic [31:0] SOUNDBIAS_REG;
logic [31:0] WAVE_RAM0_L_REG;
logic [31:0] WAVE_RAM0_H_REG;
logic [31:0] WAVE_RAM1_L_REG;
logic [31:0] WAVE_RAM1_H_REG;
logic [31:0] WAVE_RAM2_L_REG;
logic [31:0] WAVE_RAM2_H_REG;
logic [31:0] WAVE_RAM3_L_REG;
logic [31:0] WAVE_RAM3_H_REG;
logic [31:0] FIFO_A_L_REG;
logic [31:0] FIFO_A_H_REG;
logic [31:0] FIFO_B_L_REG;
logic [31:0] FIFO_B_H_REG;

logic [31:0] DMA0SAD_L_REG;
logic [31:0] DMA0SAD_H_REG;
logic [31:0] DMA0DAD_L_REG;
logic [31:0] DMA0DAD_H_REG;
logic [31:0] DMA0CNT_L_REG;
logic [31:0] DMA0CNT_H_REG;
logic [31:0] DMA1SAD_L_REG;
logic [31:0] DMA1SAD_H_REG;
logic [31:0] DMA1DAD_L_REG;
logic [31:0] DMA1DAD_H_REG;
logic [31:0] DMA1CNT_L_REG;
logic [31:0] DMA1CNT_H_REG;
logic [31:0] DMA2SAD_L_REG;
logic [31:0] DMA2SAD_H_REG;
logic [31:0] DMA2DAD_L_REG;
logic [31:0] DMA2DAD_H_REG;
logic [31:0] DMA2CNT_L_REG;
logic [31:0] DMA2CNT_H_REG;
logic [31:0] DMA3SAD_L_REG;
logic [31:0] DMA3SAD_H_REG;
logic [31:0] DMA3DAD_L_REG;
logic [31:0] DMA3DAD_H_REG;
logic [31:0] DMA3CNT_L_REG;
logic [31:0] DMA3CNT_H_REG;

logic [31:0] TM0CNT_L_REG;
logic [31:0] TM0CNT_H_REG;
logic [31:0] TM1CNT_L_REG;
logic [31:0] TM1CNT_H_REG;
logic [31:0] TM2CNT_L_REG;
logic [31:0] TM2CNT_H_REG;
logic [31:0] TM3CNT_L_REG;
logic [31:0] TM3CNT_H_REG;

logic [31:0] SIODATA32_L_REG;
logic [31:0] SIODATA32_H_REG;
logic [31:0] SIOCNT_REG;
logic [31:0] SIODATA8_REG;

logic [31:0] SIOMULTI0_REG;
logic [31:0] SIOMULTI1_REG;
logic [31:0] SIOMULTI2_REG;
logic [31:0] SIOMULTI3_REG;
logic [31:0] SIOMLT_SEND_REG;

logic [31:0] KEYINPUT_REG;
logic [31:0] KEYCNT_REG;

logic [31:0] RCNT_REG;
logic [31:0] JOYCNT_REG;
logic [31:0] JOY_RECV_L_REG;
logic [31:0] JOY_RECV_H_REG;
logic [31:0] JOY_TRANS_L_REG;
logic [31:0] JOY_TRANS_H_REG;
logic [31:0] JOYSTAT_REG;

logic [31:0] IE_REG;
logic [31:0] IF_REG;
logic [31:0] WAITCNT_REG;
logic [31:0] IME_REG;

logic [31:0] LED_REG0;
logic [31:0] LED_REG1;
logic [31:0] LED_REG2;
logic [31:0] LED_REG3;
				

    graphics_system gfx (.gfx_vram_A_addr, .gfx_vram_B_addr, .gfx_vram_C_addr,
                         .gfx_oam_addr, .gfx_palette_bg_addr,
                         .gfx_palette_obj_addr, .gfx_vram_A_addr2,

                         .gfx_vram_A_data, .gfx_vram_B_data, .gfx_vram_C_data,
                         .gfx_oam_data, .gfx_palette_bg_data,
                         .gfx_palette_obj_data, .gfx_vram_A_data2,

                         //.IO_reg_datas,
						.DISPCNT_REG(DISPCNT_REG),
						.DISPSTAT_REG(DISPSTAT_REG),
						.VCOUNT_REG(VCOUNT_REG),
						.BG0CNT_REG(BG0CNT_REG),
						.BG1CNT_REG(BG1CNT_REG),
						.BG2CNT_REG(BG2CNT_REG),
						.BG3CNT_REG(BG3CNT_REG),

						.BG0HOFS_REG(BG0HOFS_REG),
						.BG0VOFS_REG(BG0VOFS_REG),
						.BG1HOFS_REG(BG1HOFS_REG),
						.BG1VOFS_REG(BG1VOFS_REG),
						.BG2HOFS_REG(BG2HOFS_REG),
						.BG2VOFS_REG(BG2VOFS_REG),
						.BG3HOFS_REG(BG3HOFS_REG),
						.BG3VOFS_REG(BG3VOFS_REG),

						.BG2PA_REG(BG2PA_REG),
						.BG2PB_REG(BG2PB_REG),
						.BG2PC_REG(BG2PC_REG),
						.BG2PD_REG(BG2PD_REG),
						.BG2X_L_REG(BG2X_L_REG),
						.BG2X_H_REG(BG2X_H_REG),
						.BG2Y_L_REG(BG2Y_L_REG),
						.BG2Y_H_REG(BG2Y_H_REG),

						.BG3PA_REG(BG3PA_REG),
						.BG3PB_REG(BG3PB_REG),
						.BG3PC_REG(BG3PC_REG),
						.BG3PD_REG(BG3PD_REG),
						.BG3X_L_REG(BG3X_L_REG),
						.BG3X_H_REG(BG3X_H_REG),
						.BG3Y_L_REG(BG3Y_L_REG),
						.BG3Y_H_REG(BG3Y_H_REG),

						.WIN0H_REG(WIN0H_REG),
						.WIN1H_REG(WIN1H_REG),
						.WIN0V_REG(WIN0V_REG),
						.WIN1V_REG(WIN1V_REG),
						.WININ_REG(WININ_REG),
						.WINOUT_REG(WINOUT_REG),
						.MOSAIC_REG(MOSAIC_REG),

						.BLDCNT_REG(BLDCNT_REG),
						.BLDALPHA_REG(BLDALPHA_REG),
						.BLDY_REG(BLDY_REG),
						 
						 .graphics_clock(gba_clk),
                         .vga_clock(vga_clk),
                         .reset(reset), .vcount, .hcount,
                         .VGA_R, .VGA_G, .VGA_B, .VGA_HS, .VGA_VS);

    dma_top dma (.clk(gba_clk), .rst_b(~reset),
				//.registers(IO_reg_datas),
				.DMA0SAD_L_REG(DMA0SAD_L_REG),
				.DMA0SAD_H_REG(DMA0SAD_H_REG),
				.DMA0DAD_L_REG(DMA0DAD_L_REG),
				.DMA0DAD_H_REG(DMA0DAD_H_REG),
				.DMA0CNT_L_REG(DMA0CNT_L_REG),
				.DMA0CNT_H_REG(DMA0CNT_H_REG),
				.DMA1SAD_L_REG(DMA1SAD_L_REG),
				.DMA1SAD_H_REG(DMA1SAD_H_REG),
				.DMA1DAD_L_REG(DMA1DAD_L_REG),
				.DMA1DAD_H_REG(DMA1DAD_H_REG),
				.DMA1CNT_L_REG(DMA1CNT_L_REG),
				.DMA1CNT_H_REG(DMA1CNT_H_REG),
				.DMA2SAD_L_REG(DMA2SAD_L_REG),
				.DMA2SAD_H_REG(DMA2SAD_H_REG),
				.DMA2DAD_L_REG(DMA2DAD_L_REG),
				.DMA2DAD_H_REG(DMA2DAD_H_REG),
				.DMA2CNT_L_REG(DMA2CNT_L_REG),
				.DMA2CNT_H_REG(DMA2CNT_H_REG),
				.DMA3SAD_L_REG(DMA3SAD_L_REG),
				.DMA3SAD_H_REG(DMA3SAD_H_REG),
				.DMA3DAD_L_REG(DMA3DAD_L_REG),
				.DMA3DAD_H_REG(DMA3DAD_H_REG),
				.DMA3CNT_L_REG(DMA3CNT_L_REG),
				.DMA3CNT_H_REG(DMA3CNT_H_REG),
				
                 .addr(bus_addr), .rdata(bus_rdata), .wdata(bus_wdata),
                 .size(bus_size), .wen(bus_write), .active(dmaActive),
                 .disable_dma(), .irq0(dma0), .irq1(dma1), .irq2(dma2),
                 .irq3(dma3), .mem_wait(bus_pause), .sound_req1, .sound_req2,
                 .vcount(vcount), .hcount({7'd0, hcount}),
                 .cpu_preemptable);

    timer_top timers (.clock_16(gba_clk), .reset(reset),
						//.IO_reg_datas,
						.TM0CNT_L_REG(TM0CNT_L_REG),
						.TM0CNT_H_REG(TM0CNT_H_REG),
						.TM1CNT_L_REG(TM1CNT_L_REG),
						.TM1CNT_H_REG(TM1CNT_H_REG),
						.TM2CNT_L_REG(TM2CNT_L_REG),
						.TM2CNT_H_REG(TM2CNT_H_REG),
						.TM3CNT_L_REG(TM3CNT_L_REG),
						.TM3CNT_H_REG(TM3CNT_H_REG),
					
                      .internal_TM0CNT_L, .internal_TM1CNT_L, .internal_TM2CNT_L,
                      .internal_TM3CNT_L,
                      .TM0CNT_L, .TM1CNT_L, .TM2CNT_L, .TM3CNT_L,
                      .genIRQ0(timer0), .genIRQ1(timer1), .genIRQ2(timer2),
                      .genIRQ3(timer3));

					  
    gba_audio_top audio (.clk_100(clk_100), .clk_256, .gba_clk, .reset(reset),
						 /*.AC_ADR0, .AC_ADR1,
                         .AC_GPIO0, .AC_GPIO1, .AC_GPIO2, .AC_GPIO3, .AC_MCLK, .AC_SCK,
                         .AC_SDA,*/
						 .hphone_l( aud_l_24 ),
						 .hphone_r( aud_r_24 ),
						 .hphone_valid( aud_valid ),
						 
						 //.IO_reg_datas,
						.SOUND1CNT_L_REG(SOUND1CNT_L_REG),
						.SOUND1CNT_H_REG(SOUND1CNT_H_REG),
						.SOUND1CNT_X_REG(SOUND1CNT_X_REG),
						.SOUND2CNT_L_REG(SOUND2CNT_L_REG),
						.SOUND2CNT_H_REG(SOUND2CNT_H_REG),
						.SOUND3CNT_L_REG(SOUND3CNT_L_REG),
						.SOUND3CNT_H_REG(SOUND3CNT_H_REG),
						.SOUND3CNT_X_REG(SOUND3CNT_X_REG),
						.SOUND4CNT_L_REG(SOUND4CNT_L_REG),
						.SOUND4CNT_H_REG(SOUND4CNT_H_REG),
						.SOUNDCNT_L_REG(SOUNDCNT_L_REG),
						.SOUNDCNT_H_REG(SOUNDCNT_H_REG),
						.SOUNDCNT_X_REG(SOUNDCNT_X_REG),
						.SOUNDBIAS_REG(SOUNDBIAS_REG),
						.WAVE_RAM0_L_REG(WAVE_RAM0_L_REG),
						.WAVE_RAM0_H_REG(WAVE_RAM0_H_REG),
						.WAVE_RAM1_L_REG(WAVE_RAM1_L_REG),
						.WAVE_RAM1_H_REG(WAVE_RAM1_H_REG),
						.WAVE_RAM2_L_REG(WAVE_RAM2_L_REG),
						.WAVE_RAM2_H_REG(WAVE_RAM2_H_REG),
						.WAVE_RAM3_L_REG(WAVE_RAM3_L_REG),
						.WAVE_RAM3_H_REG(WAVE_RAM3_H_REG),
						.FIFO_A_L_REG(FIFO_A_L_REG),
						.FIFO_A_H_REG(FIFO_A_H_REG),
						.FIFO_B_L_REG(FIFO_B_L_REG),
						.FIFO_B_H_REG(FIFO_B_H_REG),
	
						 .sound_req1, .sound_req2,
                         .internal_TM0CNT_L, .internal_TM1CNT_L,
                         .dsASqRst, .dsBSqRst, .SW(SW[0]),

                         .FIFO_re_A, .FIFO_re_B, .FIFO_clr_A, .FIFO_clr_B, .FIFO_val_A,
                         .FIFO_val_B, .FIFO_size_A, .FIFO_size_B
                         );

logic [23:0] aud_l_24;
logic [23:0] aud_r_24;
logic aud_valid;

assign AUD_L = aud_l_24[23:8];
assign AUD_R = aud_r_24[23:8];
assign AUD_VALID = aud_valid;

    // Interface for SNES controller
    controller cont (.clock(gba_clk), .reset(reset), .data_latch(JA2),
                     .data_clock(JA3), .serial_data(JA1), .buttons);

    // Controller for debug output on LEDs
    led_controller led (.led_reg0(LED_REG0),
                        .led_reg1(LED_REG1),
                        .led_reg2(LED_REG2),
                        .led_reg3(LED_REG3),
                        .buttons, .LD, .SW);

endmodule: gba_top

// LED controller for mapping debug output
module led_controller (
    input  logic [7:0] SW,
    input  logic [31:0] led_reg0, led_reg1, led_reg2, led_reg3,
    input  logic [15:0] buttons,
    output logic [7:0] LD);

    always_comb begin
        case (SW)
            8'h0: LD = led_reg0[7:0];
            8'h1: LD = led_reg0[15:8];
            8'h2: LD = led_reg0[23:16];
            8'h3: LD = led_reg0[31:24];
            8'h4: LD = led_reg1[7:0];
            8'h5: LD = led_reg1[15:8];
            8'h6: LD = led_reg1[23:16];
            8'h7: LD = led_reg1[31:24];
            8'h8: LD = led_reg2[7:0];
            8'h9: LD = led_reg2[15:8];
            8'hA: LD = led_reg2[23:16];
            8'hB: LD = led_reg2[31:24];
            8'hC: LD = led_reg3[7:0];
            8'hD: LD = led_reg3[15:8];
            8'hE: LD = led_reg3[23:16];
            8'hF: LD = led_reg3[31:24];
            default: LD = (SW[7]) ? ~buttons[15:8] : ~buttons[7:0];
        endcase
    end
endmodule: led_controller

`default_nettype wire

/* mem_top.sv
 * Top module for the GBA memory interface. Consists of 5 BRAM regions:
 * System ROM, CPU Internal RAM, OAM, VRAM, and Palette RAM.
 *
 * "bus" I/O signals are for the CPU/DMA bus, "gfx" I/O signals are for
 * the graphics pipeline (read-only). Either port of the memory
 * controller can assert "pause" on long accesses - when this occurs,
 * whatever system is driving the memory controller's relevant input
 * signals should hold those signals constant.
 *
 * "size" refers to the size of the memory write, and assumes that the
 * data is passed to the memory controller in little endian format.
 *
 * Vivado IP Core Sizes:
 *     SystemROM: BRAM, Dual Port ROM 32x4096
 *     InternRAM: BRAM 32x8192
 *     OAM: BRAM  32x256
 *     Palette_bg: BRAM 32x128
 *     Palette_obj: BRAM 32x128
 *     VRAM_A: BRAM 32x16384
 *     VRAM_B: BRAM 32x4096
 *     VRAM_C: BRAM 32x4096
 *
 * BRAM: True Dual Ported, 32-bit address interface, reset pins on both ports,
 *     no output registers, write first operating mode, ports always enabled
 *
 * Neil Ryan, <nryan@andrew.cmu.edu>
 */

`default_nettype none
`include "../gba_core_defines.vh"
`include "../gba_mmio_defines.vh"

module mem_top (
    input  logic clock, reset,

    /* Signals for CPU/DMA Bus */
    input  logic [31:0] bus_addr,
    input  logic [31:0] bus_wdata,
    output logic [31:0] bus_rdata,
    input  logic  [1:0] bus_size,
    output logic        bus_pause,
    input  logic        bus_write,
    input  logic        dmaActive,

    // Signals for graphics Bus
    input  logic [31:0] gfx_vram_A_addr, gfx_vram_B_addr, gfx_vram_C_addr,
    input  logic [31:0] gfx_oam_addr, gfx_palette_bg_addr, gfx_palette_obj_addr,
    input  logic [31:0] gfx_vram_A_addr2,
    output logic [31:0] gfx_vram_A_data, gfx_vram_B_data, gfx_vram_C_data,
    output logic [31:0] gfx_oam_data, gfx_palette_bg_data, gfx_palette_obj_data,
    output logic [31:0] gfx_vram_A_data2,

    // IO registers
    //output logic [31:0] IO_reg_datas [`NUM_IO_REGS-1:0],

	// Graphics regs...
	output logic [31:0] DISPCNT_REG,
	output logic [31:0] DISPSTAT_REG,
	output logic [31:0] VCOUNT_REG,
	output logic [31:0] BG0CNT_REG,
	output logic [31:0] BG1CNT_REG,
	output logic [31:0] BG2CNT_REG,
	output logic [31:0] BG3CNT_REG,

	output logic [31:0] BG0HOFS_REG,
	output logic [31:0] BG0VOFS_REG,
	output logic [31:0] BG1HOFS_REG,
	output logic [31:0] BG1VOFS_REG,
	output logic [31:0] BG2HOFS_REG,
	output logic [31:0] BG2VOFS_REG,
	output logic [31:0] BG3HOFS_REG,
	output logic [31:0] BG3VOFS_REG,

	output logic [31:0] BG2PA_REG,
	output logic [31:0] BG2PB_REG,
	output logic [31:0] BG2PC_REG,
	output logic [31:0] BG2PD_REG,
	output logic [31:0] BG2X_L_REG,
	output logic [31:0] BG2X_H_REG,
	output logic [31:0] BG2Y_L_REG,
	output logic [31:0] BG2Y_H_REG,

	output logic [31:0] BG3PA_REG,
	output logic [31:0] BG3PB_REG,
	output logic [31:0] BG3PC_REG,
	output logic [31:0] BG3PD_REG,
	output logic [31:0] BG3X_L_REG,
	output logic [31:0] BG3X_H_REG,
	output logic [31:0] BG3Y_L_REG,
	output logic [31:0] BG3Y_H_REG,

	output logic [31:0] WIN0H_REG,
	output logic [31:0] WIN1H_REG,
	output logic [31:0] WIN0V_REG,
	output logic [31:0] WIN1V_REG,
	output logic [31:0] WININ_REG,
	output logic [31:0] WINOUT_REG,
	output logic [31:0] MOSAIC_REG,

	output logic [31:0] BLDCNT_REG,
	output logic [31:0] BLDALPHA_REG,
	output logic [31:0] BLDY_REG,

	
	// Audio regs...
	output logic [31:0] SOUND1CNT_L_REG,
	output logic [31:0] SOUND1CNT_H_REG,
	output logic [31:0] SOUND1CNT_X_REG,
	output logic [31:0] SOUND2CNT_L_REG,
	output logic [31:0] SOUND2CNT_H_REG,
	output logic [31:0] SOUND3CNT_L_REG,
	output logic [31:0] SOUND3CNT_H_REG,
	output logic [31:0] SOUND3CNT_X_REG,
	output logic [31:0] SOUND4CNT_L_REG,
	output logic [31:0] SOUND4CNT_H_REG,
	output logic [31:0] SOUNDCNT_L_REG,
	output logic [31:0] SOUNDCNT_H_REG,
	output logic [31:0] SOUNDCNT_X_REG,
	output logic [31:0] SOUNDBIAS_REG,
	output logic [31:0] WAVE_RAM0_L_REG,
	output logic [31:0] WAVE_RAM0_H_REG,
	output logic [31:0] WAVE_RAM1_L_REG,
	output logic [31:0] WAVE_RAM1_H_REG,
	output logic [31:0] WAVE_RAM2_L_REG,
	output logic [31:0] WAVE_RAM2_H_REG,
	output logic [31:0] WAVE_RAM3_L_REG,
	output logic [31:0] WAVE_RAM3_H_REG,
	output logic [31:0] FIFO_A_L_REG,
	output logic [31:0] FIFO_A_H_REG,
	output logic [31:0] FIFO_B_L_REG,
	output logic [31:0] FIFO_B_H_REG,

	
	// DMA regs...
	output logic [31:0] DMA0SAD_L_REG,
	output logic [31:0] DMA0SAD_H_REG,
	output logic [31:0] DMA0DAD_L_REG,
	output logic [31:0] DMA0DAD_H_REG,
	output logic [31:0] DMA0CNT_L_REG,
	output logic [31:0] DMA0CNT_H_REG,
	output logic [31:0] DMA1SAD_L_REG,
	output logic [31:0] DMA1SAD_H_REG,
	output logic [31:0] DMA1DAD_L_REG,
	output logic [31:0] DMA1DAD_H_REG,
	output logic [31:0] DMA1CNT_L_REG,
	output logic [31:0] DMA1CNT_H_REG,
	output logic [31:0] DMA2SAD_L_REG,
	output logic [31:0] DMA2SAD_H_REG,
	output logic [31:0] DMA2DAD_L_REG,
	output logic [31:0] DMA2DAD_H_REG,
	output logic [31:0] DMA2CNT_L_REG,
	output logic [31:0] DMA2CNT_H_REG,
	output logic [31:0] DMA3SAD_L_REG,
	output logic [31:0] DMA3SAD_H_REG,
	output logic [31:0] DMA3DAD_L_REG,
	output logic [31:0] DMA3DAD_H_REG,
	output logic [31:0] DMA3CNT_L_REG,
	output logic [31:0] DMA3CNT_H_REG,

	
	// Timer regs...
	output logic [31:0] TM0CNT_L_REG,
	output logic [31:0] TM0CNT_H_REG,
	output logic [31:0] TM1CNT_L_REG,
	output logic [31:0] TM1CNT_H_REG,
	output logic [31:0] TM2CNT_L_REG,
	output logic [31:0] TM2CNT_H_REG,
	output logic [31:0] TM3CNT_L_REG,
	output logic [31:0] TM3CNT_H_REG,

	
	// SIO regs...
	output logic [31:0] SIODATA32_L_REG,
	output logic [31:0] SIODATA32_H_REG,
	output logic [31:0] SIOCNT_REG,
	output logic [31:0] SIODATA8_REG,

	output logic [31:0] SIOMULTI0_REG,
	output logic [31:0] SIOMULTI1_REG,
	output logic [31:0] SIOMULTI2_REG,
	output logic [31:0] SIOMULTI3_REG,
	output logic [31:0] SIOMLT_SEND_REG,

	
	// Key regs?
	output logic [31:0] KEYINPUT_REG,
	output logic [31:0] KEYCNT_REG,

	
	// Joystick regs...
	output logic [31:0] RCNT_REG,
	output logic [31:0] JOYCNT_REG,
	output logic [31:0] JOY_RECV_L_REG,
	output logic [31:0] JOY_RECV_H_REG,
	output logic [31:0] JOY_TRANS_L_REG,
	output logic [31:0] JOY_TRANS_H_REG,
	output logic [31:0] JOYSTAT_REG,

	
	// Interrupt regs...
	output logic [31:0] IE_REG,
	output logic [31:0] IF_REG,
	output logic [31:0] WAITCNT_REG,
	output logic [31:0] IME_REG,

	
	// LED (DEBUG) regs...
	output logic [31:0] LED_REG0_REG,
	output logic [31:0] LED_REG1_REG,
	output logic [31:0] LED_REG2_REG,
	output logic [31:0] LED_REG3_REG,
	
    // Values for R/O registers
    input  logic [15:0] buttons, vcount, reg_IF,
    input  logic        vcount_match, vblank, hblank,
    output logic [15:0] int_acks,
    input  logic [15:0] internal_TM0CNT_L, internal_TM1CNT_L, internal_TM2CNT_L,
    input  logic [15:0] internal_TM3CNT_L,
    output logic [15:0] TM0CNT_L, TM1CNT_L, TM2CNT_L, TM3CNT_L,
    output logic        dsASqRst, dsBSqRst,

    // Value for DMA Sound FIFO
    input  logic        FIFO_re_A, FIFO_re_B,
    output logic [31:0] FIFO_val_A, FIFO_val_B,
    output logic [3:0]  FIFO_size_A, FIFO_size_B,
    input  logic        FIFO_clr_A, FIFO_clr_B,
	
	output logic [31:0] bus_mem_addr,
	
	output logic        bus_system_read,
	input logic  [31:0] bus_system_rdata,
	
	output logic        bus_game_read,
	input logic  [31:0] bus_game_rdata,
	
	output logic bus_io_reg_read
);


    /* Single cycle latency for writes */
    logic [31:0] bus_addr_lat1;
    logic [31:0] bus_mem_addr;
    logic  [1:0] bus_size_lat1;
    logic        bus_write_lat1;

    // DMA Bus interaction fixes (preempt cpu sync to inst. stream
    logic posedge_dmaActive, negedge_dmaActive;
    logic dmaActive_lat1;
    logic [31:0] old_cpu_rdata; // RDATA when CPU was preempted
    logic [31:0] bus_rdata_int; // Internal RDATA
    mem_register #(1) dmaA (.clock, .reset, .en(1'b1), .clr(1'b0),
                            .D(dmaActive), .Q(dmaActive_lat1));
    assign posedge_dmaActive = ~dmaActive_lat1 & dmaActive;
    assign negedge_dmaActive = dmaActive_lat1 & ~dmaActive;

    mem_register #(32) rdata (.clock, .reset, .clr(1'b0),
                              .en(posedge_dmaActive),
                              .D(bus_rdata), .Q(old_cpu_rdata));

    assign bus_rdata = (negedge_dmaActive) ? old_cpu_rdata : bus_rdata_int;


    // Could add more pauses for memory regions, this is needed
    // because of the CPU's write format

    // Use delayed memory address on writes
    assign bus_mem_addr = (bus_write_lat1) ? bus_addr_lat1 : bus_addr;

    // Registers to delay write signals
    mem_register #(32) baddr (.clock, .reset, .en(1'b1), .clr(1'b0),
                          .D(bus_addr), .Q(bus_addr_lat1));
    mem_register #(1) bwrite (.clock, .reset, .en(1'b1), .clr(1'b0),
                          .D(bus_write & ~bus_pause), .Q(bus_write_lat1));
    mem_register #(2) bsize (.clock, .reset, .en(1'b1), .clr(1'b0),
                         .D(bus_size), .Q(bus_size_lat1));
    // Pauses due to writes, could be extended
    mem_register #(1) wpause (.clock, .reset, .en(1'b1), .clr(1'b0),
                         .D(bus_write & ~bus_pause), .Q(bus_pause));

    //logic [31:0] bus_system_addr;
	//logic [31:0] bus_system_rdata;
    //logic        bus_system_read;

    logic [31:0] bus_pak_init_1_addr;
    logic        bus_pak_init_1_read;

    //logic [31:0] bus_game_addr;
	//logic [31:0] bus_game_rdata;
    //logic        bus_game_read;

    logic [31:0] bus_intern_rdata, bus_palette_rdata, bus_vram_rdata;
    logic [31:0] bus_oam_rdata;
    logic  [3:0] bus_we;

    logic [3:0]  IO_reg_we [`NUM_IO_REGS-1:0];
    logic [`NUM_IO_REGS-1:0] IO_reg_en;
    
	//tri0  [31:0] bus_io_reg_rdata;
	logic  [31:0] bus_io_reg_rdata;
    
	//logic        bus_io_reg_read;

    logic read_in_intern, read_in_palette, read_in_vram, read_in_oam;
	
    mem_decoder decoder (.addr(bus_addr_lat1), .size(bus_size_lat1),
                         .write(bus_write_lat1), .byte_we(bus_we));

    //assign bus_system_addr = bus_mem_addr;
    //assign bus_game_addr = bus_mem_addr;

    assign bus_system_read = bus_addr_lat1[31:24] == 8'h0;
    assign bus_game_read = (bus_addr_lat1[31:24] == 8'h08) ||
                           (bus_addr_lat1[31:24] == 8'h0A) ||
                           (bus_addr_lat1[31:24] == 8'h0C);

    assign bus_io_reg_read = (bus_addr_lat1 - `IO_REG_RAM_START) <= `IO_REG_RAM_SIZE;

    assign bus_pak_init_1_read = (bus_addr_lat1 - `PAK_INIT_1_START) <= `PAK_INIT_1_SIZE;
    assign bus_pak_init_1_addr = bus_addr_lat1 - `PAK_INIT_1_START;

    logic FIFO_we_A, FIFO_we_B, full_A, full_B, empty_A, empty_B;

    fifo #(32) dsA (.clk(clock), .rst(reset), .we(FIFO_we_A), .re(FIFO_re_A),
                    .full(full_A), .empty(empty_A), .data_in(bus_wdata),
                    .data_out(FIFO_val_A), .size(FIFO_size_A),
                    .clr(FIFO_clr_A));

    fifo #(32) dsB (.clk(clock), .rst(reset), .we(FIFO_we_B), .re(FIFO_re_B),
                    .full(full_B), .empty(empty_B), .data_in(bus_wdata),
                    .data_out(FIFO_val_B), .size(FIFO_size_B),
                    .clr(FIFO_clr_B));


    // Data width set to 32bits, so addresses are aligned
	/*
    system_rom sys   (.clka(clock), .rsta(reset),
                      .addra(bus_system_addr[13:2]),
                      .douta(bus_system_rdata));
	*/

	/*
    game_rom game (.clka(clock), .rsta(reset), .addra(bus_game_addr[14:2]),
                   .douta(bus_game_rdata));
	*/

    intern_mem intern (.clock, .reset, .bus_addr, .bus_addr_lat1, .bus_wdata,
                       .bus_we, .bus_write_lat1, .bus_rdata(bus_intern_rdata),
                       .read_in_intern);

    palette_mem palette (.clock, .reset, .bus_addr, .bus_addr_lat1, .bus_wdata,
                         .bus_we, .bus_write_lat1, .gfx_palette_bg_addr,
                         .gfx_palette_obj_addr, .gfx_palette_bg_data,
                         .gfx_palette_obj_data, .bus_rdata(bus_palette_rdata),
                         .read_in_palette);

    vram_mem vram (.clock, .reset, .bus_addr, .bus_addr_lat1, .bus_wdata,
                   .bus_we, .bus_write_lat1,
                   .gfx_vram_A_addr, .gfx_vram_A_addr2,
                   .gfx_vram_B_addr, .gfx_vram_C_addr,
                   .gfx_vram_A_data, .gfx_vram_A_data2,
                   .gfx_vram_B_data, .gfx_vram_C_data,
                   .bus_rdata(bus_vram_rdata),
                   .read_in_vram);

    oam_mem oam (.clock, .reset, .bus_addr, .bus_addr_lat1, .bus_wdata,
                 .bus_we, .bus_write_lat1, .gfx_oam_addr, .gfx_oam_data,
                 .bus_rdata(bus_oam_rdata), .read_in_oam);
    
    logic [15:0] vcount_reg_low_rdata;
	
	
wire io_reg_access = (bus_addr_lat1 >= `IO_REG_RAM_START && bus_addr_lat1 <= `IO_REG_RAM_END);

always_ff @(posedge clock or posedge reset)
if (reset) begin

end
else begin
	if (io_reg_access && bus_write) begin
		case ( bus_addr_lat1[31:2] )
		`DISPCNT_IDX: DISPCNT_REG <= bus_wdata;
		`VCOUNT_IDX: VCOUNT_REG <= bus_wdata;
		`BG0CNT_IDX: BG0CNT_REG <= bus_wdata;
		`BG1CNT_IDX: BG1CNT_REG <= bus_wdata;
		`BG2CNT_IDX: BG2CNT_REG <= bus_wdata;
		`BG3CNT_IDX: BG3CNT_REG <= bus_wdata;

		`BG0HOFS_IDX: BG0HOFS_REG <= bus_wdata;
		`BG0VOFS_IDX: BG0VOFS_REG <= bus_wdata;
		`BG1HOFS_IDX: BG1HOFS_REG <= bus_wdata;
		`BG1VOFS_IDX: BG1VOFS_REG <= bus_wdata;
		`BG2HOFS_IDX: BG2HOFS_REG <= bus_wdata;
		`BG2VOFS_IDX: BG2VOFS_REG <= bus_wdata;
		`BG3HOFS_IDX: BG3HOFS_REG <= bus_wdata;
		`BG3VOFS_IDX: BG3VOFS_REG <= bus_wdata;

		`BG2PA_IDX: BG2PA_REG <= bus_wdata;
		`BG2PB_IDX: BG2PB_REG <= bus_wdata;
		`BG2PC_IDX: BG2PC_REG <= bus_wdata;
		`BG2PD_IDX: BG2PD_REG <= bus_wdata;
		`BG2X_L_IDX: BG2X_L_REG <= bus_wdata;
		`BG2X_H_IDX: BG2X_H_REG <= bus_wdata;
		`BG2Y_L_IDX: BG2Y_L_REG <= bus_wdata;
		`BG2Y_H_IDX: BG2Y_H_REG <= bus_wdata;

		`BG3PA_IDX: BG3PA_REG <= bus_wdata;
		`BG3PB_IDX: BG3PB_REG <= bus_wdata;
		`BG3PC_IDX: BG3PC_REG <= bus_wdata;
		`BG3PD_IDX: BG3PD_REG <= bus_wdata;
		`BG3X_L_IDX: BG3X_L_REG <= bus_wdata;
		`BG3X_H_IDX: BG3X_H_REG <= bus_wdata;
		`BG3Y_L_IDX: BG3Y_L_REG <= bus_wdata;
		`BG3Y_H_IDX: BG3Y_H_REG <= bus_wdata;

		`WIN0H_IDX: WIN0H_REG <= bus_wdata;
		`WIN1H_IDX: WIN1H_REG <= bus_wdata;
		`WIN0V_IDX: WIN0V_REG <= bus_wdata;
		`WIN1V_IDX: WIN1V_REG <= bus_wdata;
		`WININ_IDX: WININ_REG <= bus_wdata;
		`WINOUT_IDX: WINOUT_REG <= bus_wdata;
		`MOSAIC_IDX: MOSAIC_REG <= bus_wdata;

		`BLDCNT_IDX: BLDCNT_REG <= bus_wdata;
		`BLDALPHA_IDX: BLDALPHA_REG <= bus_wdata;
		`BLDY_IDX: BLDY_REG <= bus_wdata;

		`SOUND1CNT_L_IDX: SOUND1CNT_L_REG <= bus_wdata;
		`SOUND1CNT_H_IDX: SOUND1CNT_H_REG <= bus_wdata;
		`SOUND1CNT_X_IDX: SOUND1CNT_X_REG <= bus_wdata;
		`SOUND2CNT_L_IDX: SOUND2CNT_L_REG <= bus_wdata;
		`SOUND2CNT_H_IDX: SOUND2CNT_H_REG <= bus_wdata;
		`SOUND3CNT_L_IDX: SOUND3CNT_L_REG <= bus_wdata;
		`SOUND3CNT_H_IDX: SOUND3CNT_H_REG <= bus_wdata;
		`SOUND3CNT_X_IDX: SOUND3CNT_X_REG <= bus_wdata;
		`SOUND4CNT_L_IDX: SOUND4CNT_L_REG <= bus_wdata;
		`SOUND4CNT_H_IDX: SOUND4CNT_H_REG <= bus_wdata;
		`SOUNDCNT_L_IDX: SOUNDCNT_L_REG <= bus_wdata;
		`SOUNDCNT_H_IDX: SOUNDCNT_H_REG <= bus_wdata;
		`SOUNDCNT_X_IDX: SOUNDCNT_X_REG <= bus_wdata;
		`SOUNDBIAS_IDX: SOUNDBIAS_REG <= bus_wdata;
		`WAVE_RAM0_L_IDX: WAVE_RAM0_L_REG <= bus_wdata;
		`WAVE_RAM0_H_IDX: WAVE_RAM0_H_REG <= bus_wdata;
		`WAVE_RAM1_L_IDX: WAVE_RAM1_L_REG <= bus_wdata;
		`WAVE_RAM1_H_IDX: WAVE_RAM1_H_REG <= bus_wdata;
		`WAVE_RAM2_L_IDX: WAVE_RAM2_L_REG <= bus_wdata;
		`WAVE_RAM2_H_IDX: WAVE_RAM2_H_REG <= bus_wdata;
		`WAVE_RAM3_L_IDX: WAVE_RAM3_L_REG <= bus_wdata;
		`WAVE_RAM3_H_IDX: WAVE_RAM3_H_REG <= bus_wdata;
		`FIFO_A_L: FIFO_A_L_REG <= bus_wdata;
		`FIFO_A_H: FIFO_A_H_REG <= bus_wdata;
		`FIFO_B_L: FIFO_B_L_REG <= bus_wdata;
		`FIFO_B_H: FIFO_B_H_REG <= bus_wdata;
		`DMA0SAD_L_IDX: DMA0SAD_L_REG <= bus_wdata;
		`DMA0SAD_H_IDX: DMA0SAD_H_REG <= bus_wdata;
		`DMA0DAD_L_IDX: DMA0DAD_L_REG <= bus_wdata;
		`DMA0DAD_H_IDX: DMA0DAD_H_REG <= bus_wdata;
		`DMA0CNT_L_IDX: DMA0CNT_L_REG <= bus_wdata;
		`DMA0CNT_H_IDX: DMA0CNT_H_REG <= bus_wdata;
		`DMA1SAD_L_IDX: DMA1SAD_L_REG <= bus_wdata;
		`DMA1SAD_H_IDX: DMA1SAD_H_REG <= bus_wdata;
		`DMA1DAD_L_IDX: DMA1DAD_L_REG <= bus_wdata;
		`DMA1DAD_H_IDX: DMA1DAD_H_REG <= bus_wdata;
		`DMA1CNT_L_IDX: DMA1CNT_L_REG <= bus_wdata;
		`DMA1CNT_H_IDX: DMA1CNT_H_REG <= bus_wdata;
		`DMA2SAD_L_IDX: DMA2SAD_L_REG <= bus_wdata;
		`DMA2SAD_H_IDX: DMA2SAD_H_REG <= bus_wdata;
		`DMA2DAD_L_IDX: DMA2DAD_L_REG <= bus_wdata;
		`DMA2DAD_H_IDX: DMA2DAD_H_REG <= bus_wdata;
		`DMA2CNT_L_IDX: DMA2CNT_L_REG <= bus_wdata;
		`DMA2CNT_H_IDX: DMA2CNT_H_REG <= bus_wdata;
		`DMA3SAD_L_IDX: DMA3SAD_L_REG <= bus_wdata;
		`DMA3SAD_H_IDX: DMA3SAD_H_REG <= bus_wdata;
		`DMA3DAD_L_IDX: DMA3DAD_L_REG <= bus_wdata;
		`DMA3DAD_H_IDX: DMA3DAD_H_REG <= bus_wdata;
		`DMA3CNT_L_IDX: DMA3CNT_L_REG <= bus_wdata;
		`DMA3CNT_H_IDX: DMA3CNT_H_REG <= bus_wdata;

		`TM0CNT_L_IDX: TM0CNT_L_REG <= bus_wdata;
		`TM0CNT_H_IDX: TM0CNT_H_REG <= bus_wdata;
		`TM1CNT_L_IDX: TM1CNT_L_REG <= bus_wdata;
		`TM1CNT_H_IDX: TM1CNT_H_REG <= bus_wdata;
		`TM2CNT_L_IDX: TM2CNT_L_REG <= bus_wdata;
		`TM2CNT_H_IDX: TM2CNT_H_REG <= bus_wdata;
		`TM3CNT_L_IDX: TM3CNT_L_REG <= bus_wdata;
		`TM3CNT_H_IDX: TM3CNT_H_REG <= bus_wdata;

		`SIODATA32_L_IDX: SIODATA32_L_REG <= bus_wdata;
		`SIODATA32_H_IDX: SIODATA32_H_REG <= bus_wdata;
		`SIOCNT_IDX: SIOCNT_REG <= bus_wdata;
		`SIODATA8_IDX: SIODATA8_REG <= bus_wdata;

		`SIOMULTI0_IDX: SIOMULTI0_REG <= bus_wdata;
		`SIOMULTI1_IDX: SIOMULTI1_REG <= bus_wdata;
		`SIOMULTI2_IDX: SIOMULTI2_REG <= bus_wdata;
		`SIOMULTI3_IDX: SIOMULTI3_REG <= bus_wdata;
		`SIOMLT_SEND_IDX: SIOMLT_SEND_REG <= bus_wdata;

		`KEYINPUT_IDX: KEYINPUT_REG <= bus_wdata;
		`KEYCNT_IDX: KEYCNT_REG <= bus_wdata;

		`RCNT_IDX: RCNT_REG <= bus_wdata;
		`JOYCNT_IDX: JOYCNT_REG <= bus_wdata;
		`JOY_RECV_L_IDX: JOY_RECV_L_REG <= bus_wdata;
		`JOY_RECV_H_IDX: JOY_RECV_H_REG <= bus_wdata;
		`JOY_TRANS_L_IDX: JOY_TRANS_L_REG <= bus_wdata;
		`JOY_TRANS_H_IDX: JOY_TRANS_H_REG <= bus_wdata;
		`JOYSTAT_IDX: JOYSTAT_REG <= bus_wdata;

		`IE_IDX: IE_REG <= bus_wdata;
		`IF_IDX: IF_REG <= bus_wdata;
		`WAITCNT_IDX: WAITCNT_REG <= bus_wdata;
		`IME_IDX: IME_REG <= bus_wdata;

// Unofficial registers for debug
		`LED_REG0_IDX: LED_REG0_REG <= bus_wdata;
		`LED_REG1_IDX: LED_REG1_REG <= bus_wdata;
		`LED_REG2_IDX: LED_REG2_REG <= bus_wdata;
		`LED_REG3_IDX: LED_REG3_REG <= bus_wdata;
		
		default:;
		endcase
	end
end
	

always_comb begin
		case ( bus_addr_lat1[31:2] )
		`DISPCNT_IDX: bus_io_reg_rdata = DISPCNT_REG;
		`VCOUNT_IDX: bus_io_reg_rdata = VCOUNT_REG;
		`BG0CNT_IDX: bus_io_reg_rdata = BG0CNT_REG;
		`BG1CNT_IDX: bus_io_reg_rdata = BG1CNT_REG;
		`BG2CNT_IDX: bus_io_reg_rdata = BG2CNT_REG;
		`BG3CNT_IDX: bus_io_reg_rdata = BG3CNT_REG;

		`BG0HOFS_IDX: bus_io_reg_rdata = BG0HOFS_REG;
		`BG0VOFS_IDX: bus_io_reg_rdata = BG0VOFS_REG;
		`BG1HOFS_IDX: bus_io_reg_rdata = BG1HOFS_REG;
		`BG1VOFS_IDX: bus_io_reg_rdata = BG1VOFS_REG;
		`BG2HOFS_IDX: bus_io_reg_rdata = BG2HOFS_REG;
		`BG2VOFS_IDX: bus_io_reg_rdata = BG2VOFS_REG;
		`BG3HOFS_IDX: bus_io_reg_rdata = BG3HOFS_REG;
		`BG3VOFS_IDX: bus_io_reg_rdata = BG3VOFS_REG;

		`BG2PA_IDX: bus_io_reg_rdata = BG2PA_REG;
		`BG2PB_IDX: bus_io_reg_rdata = BG2PB_REG;
		`BG2PC_IDX: bus_io_reg_rdata = BG2PC_REG;
		`BG2PD_IDX: bus_io_reg_rdata = BG2PD_REG;
		`BG2X_L_IDX: bus_io_reg_rdata = BG2X_L_REG;
		`BG2X_H_IDX: bus_io_reg_rdata = BG2X_H_REG;
		`BG2Y_L_IDX: bus_io_reg_rdata = BG2Y_L_REG;
		`BG2Y_H_IDX: bus_io_reg_rdata = BG2Y_H_REG;

		`BG3PA_IDX: bus_io_reg_rdata = BG3PA_REG;
		`BG3PB_IDX: bus_io_reg_rdata = BG3PB_REG;
		`BG3PC_IDX: bus_io_reg_rdata = BG3PC_REG;
		`BG3PD_IDX: bus_io_reg_rdata = BG3PD_REG;
		`BG3X_L_IDX: bus_io_reg_rdata = BG3X_L_REG;
		`BG3X_H_IDX: bus_io_reg_rdata = BG3X_H_REG;
		`BG3Y_L_IDX: bus_io_reg_rdata = BG3Y_L_REG;
		`BG3Y_H_IDX: bus_io_reg_rdata = BG3Y_H_REG;

		`WIN0H_IDX: bus_io_reg_rdata = WIN0H_REG;
		`WIN1H_IDX: bus_io_reg_rdata = WIN1H_REG;
		`WIN0V_IDX: bus_io_reg_rdata = WIN0V_REG;
		`WIN1V_IDX: bus_io_reg_rdata = WIN1V_REG;
		`WININ_IDX: bus_io_reg_rdata = WININ_REG;
		`WINOUT_IDX: bus_io_reg_rdata = WINOUT_REG;
		`MOSAIC_IDX: bus_io_reg_rdata = MOSAIC_REG;

		`BLDCNT_IDX: bus_io_reg_rdata = BLDCNT_REG;
		`BLDALPHA_IDX: bus_io_reg_rdata = BLDALPHA_REG;
		`BLDY_IDX: bus_io_reg_rdata = BLDY_REG;

		`SOUND1CNT_L_IDX: bus_io_reg_rdata = SOUND1CNT_L_REG;
		`SOUND1CNT_H_IDX: bus_io_reg_rdata = SOUND1CNT_H_REG;
		`SOUND1CNT_X_IDX: bus_io_reg_rdata = SOUND1CNT_X_REG;
		`SOUND2CNT_L_IDX: bus_io_reg_rdata = SOUND2CNT_L_REG;
		`SOUND2CNT_H_IDX: bus_io_reg_rdata = SOUND2CNT_H_REG;
		`SOUND3CNT_L_IDX: bus_io_reg_rdata = SOUND3CNT_L_REG;
		`SOUND3CNT_H_IDX: bus_io_reg_rdata = SOUND3CNT_H_REG;
		`SOUND3CNT_X_IDX: bus_io_reg_rdata = SOUND3CNT_X_REG;
		`SOUND4CNT_L_IDX: bus_io_reg_rdata = SOUND4CNT_L_REG;
		`SOUND4CNT_H_IDX: bus_io_reg_rdata = SOUND4CNT_H_REG;
		`SOUNDCNT_L_IDX: bus_io_reg_rdata = SOUNDCNT_L_REG;
		`SOUNDCNT_H_IDX: bus_io_reg_rdata = SOUNDCNT_H_REG;
		`SOUNDCNT_X_IDX: bus_io_reg_rdata = SOUNDCNT_X_REG;
		`SOUNDBIAS_IDX: bus_io_reg_rdata = SOUNDBIAS_REG;
		`WAVE_RAM0_L_IDX: bus_io_reg_rdata = WAVE_RAM0_L_REG;
		`WAVE_RAM0_H_IDX: bus_io_reg_rdata = WAVE_RAM0_H_REG;
		`WAVE_RAM1_L_IDX: bus_io_reg_rdata = WAVE_RAM1_L_REG;
		`WAVE_RAM1_H_IDX: bus_io_reg_rdata = WAVE_RAM1_H_REG;
		`WAVE_RAM2_L_IDX: bus_io_reg_rdata = WAVE_RAM2_L_REG;
		`WAVE_RAM2_H_IDX: bus_io_reg_rdata = WAVE_RAM2_H_REG;
		`WAVE_RAM3_L_IDX: bus_io_reg_rdata = WAVE_RAM3_L_REG;
		`WAVE_RAM3_H_IDX: bus_io_reg_rdata = WAVE_RAM3_H_REG;
		`FIFO_A_L: bus_io_reg_rdata = FIFO_A_L_REG;
		`FIFO_A_H: bus_io_reg_rdata = FIFO_A_H_REG;
		`FIFO_B_L: bus_io_reg_rdata = FIFO_B_L_REG;
		`FIFO_B_H: bus_io_reg_rdata = FIFO_B_H_REG;
		`DMA0SAD_L_IDX: bus_io_reg_rdata = DMA0SAD_L_REG;
		`DMA0SAD_H_IDX: bus_io_reg_rdata = DMA0SAD_H_REG;
		`DMA0DAD_L_IDX: bus_io_reg_rdata = DMA0DAD_L_REG;
		`DMA0DAD_H_IDX: bus_io_reg_rdata = DMA0DAD_H_REG;
		`DMA0CNT_L_IDX: bus_io_reg_rdata = DMA0CNT_L_REG;
		`DMA0CNT_H_IDX: bus_io_reg_rdata = DMA0CNT_H_REG;
		`DMA1SAD_L_IDX: bus_io_reg_rdata = DMA1SAD_L_REG;
		`DMA1SAD_H_IDX: bus_io_reg_rdata = DMA1SAD_H_REG;
		`DMA1DAD_L_IDX: bus_io_reg_rdata = DMA1DAD_L_REG;
		`DMA1DAD_H_IDX: bus_io_reg_rdata = DMA1DAD_H_REG;
		`DMA1CNT_L_IDX: bus_io_reg_rdata = DMA1CNT_L_REG;
		`DMA1CNT_H_IDX: bus_io_reg_rdata = DMA1CNT_H_REG;
		`DMA2SAD_L_IDX: bus_io_reg_rdata = DMA2SAD_L_REG;
		`DMA2SAD_H_IDX: bus_io_reg_rdata = DMA2SAD_H_REG;
		`DMA2DAD_L_IDX: bus_io_reg_rdata = DMA2DAD_L_REG;
		`DMA2DAD_H_IDX: bus_io_reg_rdata = DMA2DAD_H_REG;
		`DMA2CNT_L_IDX: bus_io_reg_rdata = DMA2CNT_L_REG;
		`DMA2CNT_H_IDX: bus_io_reg_rdata = DMA2CNT_H_REG;
		`DMA3SAD_L_IDX: bus_io_reg_rdata = DMA3SAD_L_REG;
		`DMA3SAD_H_IDX: bus_io_reg_rdata = DMA3SAD_H_REG;
		`DMA3DAD_L_IDX: bus_io_reg_rdata = DMA3DAD_L_REG;
		`DMA3DAD_H_IDX: bus_io_reg_rdata = DMA3DAD_H_REG;
		`DMA3CNT_L_IDX: bus_io_reg_rdata = DMA3CNT_L_REG;
		`DMA3CNT_H_IDX: bus_io_reg_rdata = DMA3CNT_H_REG;

		`TM0CNT_L_IDX: bus_io_reg_rdata = TM0CNT_L_REG;
		`TM0CNT_H_IDX: bus_io_reg_rdata = TM0CNT_H_REG;
		`TM1CNT_L_IDX: bus_io_reg_rdata = TM1CNT_L_REG;
		`TM1CNT_H_IDX: bus_io_reg_rdata = TM1CNT_H_REG;
		`TM2CNT_L_IDX: bus_io_reg_rdata = TM2CNT_L_REG;
		`TM2CNT_H_IDX: bus_io_reg_rdata = TM2CNT_H_REG;
		`TM3CNT_L_IDX: bus_io_reg_rdata = TM3CNT_L_REG;
		`TM3CNT_H_IDX: bus_io_reg_rdata = TM3CNT_H_REG;

		`SIODATA32_L_IDX: bus_io_reg_rdata = SIODATA32_L_REG;
		`SIODATA32_H_IDX: bus_io_reg_rdata = SIODATA32_H_REG;
		`SIOCNT_IDX: bus_io_reg_rdata = SIOCNT_REG;
		`SIODATA8_IDX: bus_io_reg_rdata = SIODATA8_REG;

		`SIOMULTI0_IDX: bus_io_reg_rdata = SIOMULTI0_REG;
		`SIOMULTI1_IDX: bus_io_reg_rdata = SIOMULTI1_REG;
		`SIOMULTI2_IDX: bus_io_reg_rdata = SIOMULTI2_REG;
		`SIOMULTI3_IDX: bus_io_reg_rdata = SIOMULTI3_REG;
		`SIOMLT_SEND_IDX: bus_io_reg_rdata = SIOMLT_SEND_REG;

		`KEYINPUT_IDX: bus_io_reg_rdata = KEYINPUT_REG;
		`KEYCNT_IDX: bus_io_reg_rdata = KEYCNT_REG;

		`RCNT_IDX: bus_io_reg_rdata = RCNT_REG;
		`JOYCNT_IDX: bus_io_reg_rdata = JOYCNT_REG;
		`JOY_RECV_L_IDX: bus_io_reg_rdata = JOY_RECV_L_REG;
		`JOY_RECV_H_IDX: bus_io_reg_rdata = JOY_RECV_H_REG;
		`JOY_TRANS_L_IDX: bus_io_reg_rdata = JOY_TRANS_L_REG;
		`JOY_TRANS_H_IDX: bus_io_reg_rdata = JOY_TRANS_H_REG;
		`JOYSTAT_IDX: bus_io_reg_rdata = JOYSTAT_REG;

		`IE_IDX: bus_io_reg_rdata = IE_REG;
		`IF_IDX: bus_io_reg_rdata = IF_REG;
		`WAITCNT_IDX: bus_io_reg_rdata = WAITCNT_REG;
		`IME_IDX: bus_io_reg_rdata = IME_REG;

// Unofficial registers for debug
		//`LED_REG0_IDX: bus_io_reg_rdata = LED_REG0_REG <= bus_wdata;
		//`LED_REG1_IDX: bus_io_reg_rdata = LED_REG1_REG <= bus_wdata;
		//`LED_REG2_IDX: bus_io_reg_rdata = LED_REG2_REG <= bus_wdata;
		//`LED_REG3_IDX: bus_io_reg_rdata = LED_REG3_REG <= bus_wdata;
		
	default:;
	endcase
end
	
	
/*
	output logic [31:0] DISPCNT_REG,
	output logic [31:0] DISPSTAT_REG,
	output logic [31:0] VCOUNT_REG,
	output logic [31:0] BG0CNT_REG,
	output logic [31:0] BG1CNT_REG,
	output logic [31:0] BG2CNT_REG,
	output logic [31:0] BG3CNT_REG,

	output logic [31:0] BG0HOFS_REG,
	output logic [31:0] BG0VOFS_REG,
	output logic [31:0] BG1HOFS_REG,
	output logic [31:0] BG1VOFS_REG,
	output logic [31:0] BG2HOFS_REG,
	output logic [31:0] BG2VOFS_REG,
	output logic [31:0] BG3HOFS_REG,
	output logic [31:0] BG3VOFS_REG,

	output logic [31:0] BG2PA_REG,
	output logic [31:0] BG2PB_REG,
	output logic [31:0] BG2PC_REG,
	output logic [31:0] BG2PD_REG,
	output logic [31:0] BG2X_L_REG,
	output logic [31:0] BG2X_H_REG,
	output logic [31:0] BG2Y_L_REG,
	output logic [31:0] BG2Y_H_REG,

	output logic [31:0] BG3PA_REG,
	output logic [31:0] BG3PB_REG,
	output logic [31:0] BG3PC_REG,
	output logic [31:0] BG3PD_REG,
	output logic [31:0] BG3X_L_REG,
	output logic [31:0] BG3X_H_REG,
	output logic [31:0] BG3Y_L_REG,
	output logic [31:0] BG3Y_H_REG,

	output logic [31:0] WIN0H_REG,
	output logic [31:0] WIN1H_REG,
	output logic [31:0] WIN0V_REG,
	output logic [31:0] WIN1V_REG,
	output logic [31:0] WININ_REG,
	output logic [31:0] WINOUT_REG,
	output logic [31:0] MOSAIC_REG,

	output logic [31:0] BLDCNT_REG,
	output logic [31:0] BLDALPHA_REG,
	output logic [31:0] BLDY_REG,

	
	// Audio regs...
	output logic [31:0] SOUND1CNT_L_REG,
	output logic [31:0] SOUND1CNT_H_REG,
	output logic [31:0] SOUND1CNT_X_REG,
	output logic [31:0] SOUND2CNT_L_REG,
	output logic [31:0] SOUND2CNT_H_REG,
	output logic [31:0] SOUND3CNT_L_REG,
	output logic [31:0] SOUND3CNT_H_REG,
	output logic [31:0] SOUND3CNT_X_REG,
	output logic [31:0] SOUND4CNT_L_REG,
	output logic [31:0] SOUND4CNT_H_REG,
	output logic [31:0] SOUNDCNT_L_REG,
	output logic [31:0] SOUNDCNT_H_REG,
	output logic [31:0] SOUNDCNT_X_REG,
	output logic [31:0] SOUNDBIAS_REG,
	output logic [31:0] WAVE_RAM0_L_REG,
	output logic [31:0] WAVE_RAM0_H_REG,
	output logic [31:0] WAVE_RAM1_L_REG,
	output logic [31:0] WAVE_RAM1_H_REG,
	output logic [31:0] WAVE_RAM2_L_REG,
	output logic [31:0] WAVE_RAM2_H_REG,
	output logic [31:0] WAVE_RAM3_L_REG,
	output logic [31:0] WAVE_RAM3_H_REG,
	output logic [31:0] FIFO_A_L_REG,
	output logic [31:0] FIFO_A_H_REG,
	output logic [31:0] FIFO_B_L_REG,
	output logic [31:0] FIFO_B_H_REG,

	
	// DMA regs...
	output logic [31:0] DMA0SAD_L_REG,
	output logic [31:0] DMA0SAD_H_REG,
	output logic [31:0] DMA0DAD_L_REG,
	output logic [31:0] DMA0DAD_H_REG,
	output logic [31:0] DMA0CNT_L_REG,
	output logic [31:0] DMA0CNT_H_REG,
	output logic [31:0] DMA1SAD_L_REG,
	output logic [31:0] DMA1SAD_H_REG,
	output logic [31:0] DMA1DAD_L_REG,
	output logic [31:0] DMA1DAD_H_REG,
	output logic [31:0] DMA1CNT_L_REG,
	output logic [31:0] DMA1CNT_H_REG,
	output logic [31:0] DMA2SAD_L_REG,
	output logic [31:0] DMA2SAD_H_REG,
	output logic [31:0] DMA2DAD_L_REG,
	output logic [31:0] DMA2DAD_H_REG,
	output logic [31:0] DMA2CNT_L_REG,
	output logic [31:0] DMA2CNT_H_REG,
	output logic [31:0] DMA3SAD_L_REG,
	output logic [31:0] DMA3SAD_H_REG,
	output logic [31:0] DMA3DAD_L_REG,
	output logic [31:0] DMA3DAD_H_REG,
	output logic [31:0] DMA3CNT_L_REG,
	output logic [31:0] DMA3CNT_H_REG,

	
	// Timer regs...
	output logic [31:0] TM0CNT_L_REG,
	output logic [31:0] TM0CNT_H_REG,
	output logic [31:0] TM1CNT_L_REG,
	output logic [31:0] TM1CNT_H_REG,
	output logic [31:0] TM2CNT_L_REG,
	output logic [31:0] TM2CNT_H_REG,
	output logic [31:0] TM3CNT_L_REG,
	output logic [31:0] TM3CNT_H_REG,

	
	// SIO regs...
	output logic [31:0] SIODATA32_L_REG,
	output logic [31:0] SIODATA32_H_REG,
	output logic [31:0] SIOCNT_REG,
	output logic [31:0] SIODATA8_REG,

	output logic [31:0] SIOMULTI0_REG,
	output logic [31:0] SIOMULTI1_REG,
	output logic [31:0] SIOMULTI2_REG,
	output logic [31:0] SIOMULTI3_REG,
	output logic [31:0] SIOMLT_SEND_REG,

	
	// Key regs?
	output logic [31:0] KEYINPUT_REG,
	output logic [31:0] KEYCNT_REG,

	
	// Joystick regs...
	output logic [31:0] RCNT_REG,
	output logic [31:0] JOYCNT_REG,
	output logic [31:0] JOY_RECV_L_REG,
	output logic [31:0] JOY_RECV_H_REG,
	output logic [31:0] JOY_TRANS_L_REG,
	output logic [31:0] JOY_TRANS_H_REG,
	output logic [31:0] JOYSTAT_REG,

	
	// Interrupt regs...
	output logic [31:0] IE_REG,
	output logic [31:0] IF_REG,
	output logic [31:0] WAITCNT_REG,
	output logic [31:0] IME_REG,

	
	// LED (DEBUG) regs...
	output logic [31:0] LED_REG0_REG,
	output logic [31:0] LED_REG1_REG,
	output logic [31:0] LED_REG2_REG,
	output logic [31:0] LED_REG3_REG,
*/

// `define IO_REG_RAM_START 32'h0400_0000
// `define IO_REG_RAM_END   32'h0400_0807 // From GBATEK
// `define IO_REG_RAM_SIZE (`IO_REG_RAM_END-`IO_REG_RAM_START)
	
	
	/*
    generate
        for (genvar i = 0; i < `NUM_IO_REGS; i++) begin
            localparam [31:0] reg_addr = `IO_REG_RAM_START + (i*4);
            assign IO_reg_en[i] = bus_addr_lat1[31:2] == reg_addr[31:2];
            assign IO_reg_we[i] = (IO_reg_en[i]) ? bus_we : 4'd0;
            assign bus_io_reg_rdata = (IO_reg_en[i]) ? IO_reg_datas[i] : 32'bz;
            if (i == `KEYINPUT_IDX) begin // Read-only for lowest 16 bits
                IO_register16 key_high (.clock, .reset, .wdata(bus_wdata[31:16]),
                                        .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                        .rdata(IO_reg_datas[i][31:16]));
                assign IO_reg_datas[i][15:0] = buttons;
            end else if (i == `VCOUNT_IDX) begin // Read-only for upper 16 bits
                IO_register16 vcount_low
                              (.clock, .reset, .wdata(bus_wdata[15:0]),
                               .we(IO_reg_we[i][1:0]), .clear(1'b0),
                               .rdata(vcount_reg_low_rdata));
                assign IO_reg_datas[i][15:0]  = {vcount_reg_low_rdata[15:3], vcount_match, hblank, vblank};
                assign IO_reg_datas[i][31:16] = vcount;
            end else if (i == `IF_IDX) begin
                // Reads to 0x202 read re_IF
                IO_register16 IE (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(IO_reg_datas[i][15:0]));
                IO_register16 IACK (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b1),
                                    .rdata(int_acks));
                assign IO_reg_datas[i][31:16] = reg_IF;
            end else if (i == `TM0CNT_L_IDX) begin
                // Reads to low read current counter value
                IO_register16 T0_L (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(TM0CNT_L));
                IO_register16 T0_H (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                    .rdata(IO_reg_datas[i][31:16]));
                assign IO_reg_datas[i][15:0] = internal_TM0CNT_L;
            end else if (i == `TM1CNT_L_IDX) begin
                // Reads to low read current counter value
                IO_register16 T1_L (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(TM1CNT_L));
                IO_register16 T1_H (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                    .rdata(IO_reg_datas[i][31:16]));
                assign IO_reg_datas[i][15:0] = internal_TM1CNT_L;
            end else if (i == `TM2CNT_L_IDX) begin
                // Reads to low read current counter value
                IO_register16 T2_L (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(TM2CNT_L));
                IO_register16 T2_H (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                    .rdata(IO_reg_datas[i][31:16]));
                assign IO_reg_datas[i][15:0] = internal_TM2CNT_L;
            end else if (i == `TM3CNT_L_IDX) begin
                // Reads to low read current counter value
                IO_register16 T3_L (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(TM3CNT_L));
                IO_register16 T3_H (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                    .rdata(IO_reg_datas[i][31:16]));
                assign IO_reg_datas[i][15:0] = internal_TM3CNT_L;
            end else if (i == `SOUNDCNT_H_IDX) begin
                // Reads to low read current counter value
                IO_register16 SCH_L (.clock, .reset, .wdata(bus_wdata[15:0]),
                                  .we(IO_reg_we[i][1:0]), .clear(1'b0),
                                  .rdata(IO_reg_datas[i][15:0]));
                IO_register16 SCH_H (.clock, .reset, .wdata(bus_wdata[31:16]),
                                    .we(IO_reg_we[i][3:2]), .clear(1'b0),
                                    .rdata(IO_reg_datas[i][31:16]));
                assign dsASqRst = IO_reg_we[i][3] & bus_wdata[27];
                assign dsBSqRst = IO_reg_we[i][3] & bus_wdata[31];
            end else if (i == `FIFO_A_L) begin
                assign IO_reg_datas[i] = FIFO_val_A;
                assign FIFO_we_A = IO_reg_we[i][0];
            end else if (i == `FIFO_B_L) begin
                assign IO_reg_datas[i] = FIFO_val_B;
                assign FIFO_we_B = IO_reg_we[i][0];
            end else begin
                IO_register32 IO (.clock, .reset, .wdata(bus_wdata),
                                  .we(IO_reg_we[i]), .rdata(IO_reg_datas[i]));
            end
        end
    endgenerate
	*/

    always_comb begin
        if (bus_system_read)
            bus_rdata_int = bus_system_rdata;
        else if (read_in_intern)
            bus_rdata_int = bus_intern_rdata;
        else if (read_in_vram)
            bus_rdata_int = bus_vram_rdata;
        else if (read_in_palette)
            bus_rdata_int = bus_palette_rdata;
        else if (read_in_oam)
            bus_rdata_int = bus_oam_rdata;
        else if (bus_io_reg_read)
            bus_rdata_int = bus_io_reg_rdata;
        else if (bus_pak_init_1_read)
            bus_rdata_int = {12'hFFF, bus_pak_init_1_addr[4:2], 1'b1,
							 12'hFFF, bus_pak_init_1_addr[4:2], 1'b0};
        else if (bus_game_read)
            bus_rdata_int = bus_game_rdata;
        else
            bus_rdata_int = 32'h0;
    end

endmodule: mem_top

module intern_mem (
    input logic clock, reset,

    input  logic [31:0] bus_addr, bus_addr_lat1, bus_wdata,
    input  logic  [3:0] bus_we,
    input  logic        bus_write_lat1,
    output logic [31:0] bus_rdata,
    output logic        read_in_intern

    );

    logic [31:0] intern_addr, intern_rdata;
    logic  [3:0] intern_we;
    logic        in_intern_lat1;

    assign read_in_intern = in_intern_lat1;
    assign in_intern_lat1 = bus_addr_lat1[31:24] == 8'h03;
    assign intern_addr = (bus_write_lat1) ? bus_addr_lat1 : bus_addr;
    assign intern_we = (in_intern_lat1) ? bus_we : 4'd0;

    assign bus_rdata = (in_intern_lat1) ? intern_rdata : 32'bz;

    InternRAM intern (.clka(clock), .rsta(reset),
                      .wea(intern_we), .addra(intern_addr[14:2]),
                      .douta(intern_rdata), .dina(bus_wdata),

                      .clkb(clock), .rstb(reset), .web(4'd0), .addrb(32'b0),
                      .doutb(), .dinb(32'b0));

endmodule: intern_mem


module oam_mem (
    input logic clock, reset,

    input  logic [31:0] bus_addr, bus_addr_lat1, bus_wdata,
    input  logic  [3:0] bus_we,
    input  logic        bus_write_lat1,
    input  logic [31:0] gfx_oam_addr,
    output logic [31:0] gfx_oam_data, bus_rdata,
    output logic        read_in_oam

    );

    logic [31:0] oam_addr, oam_rdata;
    logic  [3:0] oam_we;
    logic        in_oam_lat1;

    assign read_in_oam = in_oam_lat1;
    assign in_oam_lat1 = bus_addr_lat1[31:24] == 8'h07;
    assign oam_addr = (bus_write_lat1) ? bus_addr_lat1 : bus_addr;
    assign oam_we = (in_oam_lat1) ? bus_we : 4'd0;

    assign bus_rdata = (in_oam_lat1) ? oam_rdata : 32'bz;

    OAM oam_mem  (.clka(clock), .rsta(reset),
                  .wea(oam_we), .addra(oam_addr[9:2]),
                  .douta(oam_rdata), .dina(bus_wdata),

                  .clkb(clock), .rstb(reset),
                  .web(4'd0), .addrb(gfx_oam_addr[9:2]),
                  .doutb(gfx_oam_data), .dinb(32'b0));

endmodule: oam_mem

module palette_mem (
    input logic clock, reset,

    input  logic [31:0] bus_addr, bus_addr_lat1, bus_wdata,
    input  logic  [3:0] bus_we,
    input  logic        bus_write_lat1,
    input  logic [31:0] gfx_palette_bg_addr, gfx_palette_obj_addr,
    output logic [31:0] gfx_palette_bg_data, gfx_palette_obj_data,
    output logic [31:0] bus_rdata,
    output logic        read_in_palette
    );

    logic [31:0] palette_bg_addr, palette_obj_addr;
    logic [31:0] palette_bg_rdata, palette_obj_rdata;
    logic  [3:0] palette_bg_we, palette_obj_we;
    logic        in_palette_lat1, in_palette_bg_lat1, in_palette_obj_lat1;

    assign read_in_palette = in_palette_lat1;
    assign in_palette_lat1 = bus_addr_lat1[31:24] == 8'h05;
    assign in_palette_bg_lat1 = in_palette_lat1 &
                                (bus_addr_lat1[9:0] <= 10'h1FF);
    assign in_palette_obj_lat1 = in_palette_lat1 &
                           (bus_addr_lat1[9:0] <= 10'h3FF) &
                           (10'h200 <= bus_addr_lat1[9:0]);

    assign palette_bg_addr = (bus_write_lat1) ? bus_addr_lat1 : bus_addr;
    assign palette_obj_addr = (bus_write_lat1) ?
                               bus_addr_lat1 - `PALETTE_OBJ_RAM_START :
                               bus_addr - `PALETTE_OBJ_RAM_START;

    assign palette_bg_we = (in_palette_bg_lat1) ? bus_we : 4'd0;
    assign palette_obj_we = (in_palette_obj_lat1) ? bus_we : 4'd0;

    always_comb begin
        if (in_palette_bg_lat1)
            bus_rdata = palette_bg_rdata;
        else if (in_palette_obj_lat1)
            bus_rdata = palette_obj_rdata;
        else
            bus_rdata = 32'bz;
    end

    palette_bg_ram pall_bg (.clka(clock), .rsta(reset),
                            .wea(palette_bg_we),
                            .addra(palette_bg_addr[8:2]),
                            .douta(palette_bg_rdata), .dina(bus_wdata),

                            .clkb(clock), .rstb(reset),
                            .web(4'd0),
                            .addrb(gfx_palette_bg_addr[8:2]),
                            .doutb(gfx_palette_bg_data), .dinb(32'b0));

    palette_obj_ram pall_obj (.clka(clock), .rsta(reset),
                              .wea(palette_obj_we),
                              .addra(palette_obj_addr[8:2]),
                              .douta(palette_obj_rdata), .dina(bus_wdata),

                              .clkb(clock), .rstb(reset),
                              .web(4'd0),
                              .addrb(gfx_palette_obj_addr[8:2]),
                              .doutb(gfx_palette_obj_data), .dinb(32'b0));

endmodule: palette_mem

module vram_mem (
    input  logic clock, reset,

    input  logic [31:0] bus_addr, bus_addr_lat1, bus_wdata,
    input  logic  [3:0] bus_we,
    input  logic        bus_write_lat1,
    input  logic [31:0] gfx_vram_A_addr, gfx_vram_A_addr2,
    input  logic [31:0] gfx_vram_B_addr, gfx_vram_C_addr,
    output logic [31:0] gfx_vram_A_data, gfx_vram_A_data2,
    output logic [31:0] gfx_vram_B_data, gfx_vram_C_data,
    output logic [31:0] bus_rdata,
    output logic        read_in_vram
    );

    logic [31:0] vram_A_addr, vram_B_addr, vram_C_addr;
    logic [31:0] vram_A_rdata, vram_B_rdata, vram_C_rdata;
    logic [3:0] vram_A_we, vram_B_we, vram_C_we;
    logic       in_vram_lat1;
    logic       in_vram_A_lat1, in_vram_B_lat1, in_vram_C_lat1;

    assign read_in_vram = in_vram_lat1;
    assign in_vram_lat1 = bus_addr_lat1[31:24] == 8'h06;
    assign in_vram_A_lat1 = in_vram_lat1 &
                            (bus_addr_lat1[16:0] <= 17'hFFFF);
    assign in_vram_B_lat1 = in_vram_lat1 &
                            (bus_addr_lat1[16:0] <= 17'h13FFF) &
                            (17'h10000 <= bus_addr_lat1[16:0]);
    assign in_vram_C_lat1 = in_vram_lat1 &
                            (bus_addr_lat1[16:0] <= 17'h17FFF) &
                            (17'h14000 <= bus_addr_lat1[16:0]);

    assign vram_A_addr = (bus_write_lat1) ? bus_addr_lat1 : bus_addr;
    assign vram_B_addr = (bus_write_lat1) ? bus_addr_lat1 - `VRAM_B_START :
                         bus_addr - `VRAM_B_START;
    assign vram_C_addr = (bus_write_lat1) ? bus_addr_lat1 - `VRAM_C_START :
                          bus_addr - `VRAM_C_START;

    assign vram_A_we = (in_vram_A_lat1) ? bus_we : 4'd0;
    assign vram_B_we = (in_vram_B_lat1) ? bus_we : 4'd0;
    assign vram_C_we = (in_vram_C_lat1) ? bus_we : 4'd0;

    always_comb begin
        if (in_vram_A_lat1)
            bus_rdata = vram_A_rdata;
        else if (in_vram_B_lat1)
            bus_rdata = vram_B_rdata;
        else if (in_vram_C_lat1)
            bus_rdata = vram_C_rdata;
        else
            bus_rdata = 32'bz;
    end

    vram_A vram_A    (.clka(clock), .rsta(reset),
                      .wea(vram_A_we), .addra(vram_A_addr[15:2]),
                      .douta(vram_A_rdata), .dina(bus_wdata),

                      .clkb(clock), .rstb(reset),
                      .web(4'd0), .addrb(gfx_vram_A_addr[15:2]),
                      .doutb(gfx_vram_A_data), .dinb(32'b0));

    vram_A_2 vram_A_2 (.clka(clock), .rsta(reset),
                      .wea(vram_A_we), .addra(vram_A_addr[15:2]),
                      .douta(), .dina(bus_wdata),

                      .clkb(clock), .rstb(reset),
                      .web(4'd0), .addrb(gfx_vram_A_addr2[15:2]),
                      .doutb(gfx_vram_A_data2), .dinb(32'b0));

    vram_B vram_B    (.clka(clock), .rsta(reset),
                      .wea(vram_B_we), .addra(vram_B_addr[13:2]),
                      .douta(vram_B_rdata), .dina(bus_wdata),

                      .clkb(clock), .rstb(reset),
                      .web(4'd0), .addrb(gfx_vram_B_addr[13:2]),
                      .doutb(gfx_vram_B_data), .dinb(32'b0));
    
    vram_C vram_C    (.clka(clock), .rsta(reset),
                      .wea(vram_C_we), .addra(vram_C_addr[13:2]),
                      .douta(vram_C_rdata), .dina(bus_wdata),

                      .clkb(clock), .rstb(reset),
                      .web(4'd0), .addrb(gfx_vram_C_addr[13:2]),
                      .doutb(gfx_vram_C_data), .dinb(32'b0));
    
endmodule: vram_mem

/* Setup byte write enables for memory (assumes that CPU deals with
 * endianness!) */
module mem_decoder
    (input  logic [31:0] addr,
     input  logic [1:0]  size,
     input  logic        write,
     output logic [3:0]  byte_we);

     always_comb begin
         byte_we = 4'd0;
         if (write) begin
             byte_we[3] = (addr[1:0] == 2'd3 && size == `MEM_SIZE_BYTE) ||
                          (addr[1] && size == `MEM_SIZE_HALF) ||
                          (size == `MEM_SIZE_WORD);

             byte_we[2] = (addr[1:0] == 2'd2 && size == `MEM_SIZE_BYTE) ||
                          (addr[1] && size == `MEM_SIZE_HALF) ||
                          (size == `MEM_SIZE_WORD);

             byte_we[1] = (addr[1:0] == 2'd1 && size == `MEM_SIZE_BYTE) ||
                          (~addr[1] && size == `MEM_SIZE_HALF) ||
                          (size == `MEM_SIZE_WORD);

             byte_we[0] = (addr[1:0] == 2'd0 && size == `MEM_SIZE_BYTE) ||
                          (~addr[1] && size == `MEM_SIZE_HALF) ||
                          (size == `MEM_SIZE_WORD);
         end
     end

endmodule: mem_decoder

module mem_register
    #(parameter WIDTH = 8)
    (input  logic clock, reset,
     output logic [WIDTH-1:0] Q,
     input  logic [WIDTH-1:0] D,
     input  logic en, clr);

    logic [WIDTH-1:0] D_next;
    assign D_next = (clr) ? 0 : ((en) ? D : Q);

    always_ff @(posedge clock, posedge reset) begin
        if (reset) Q <= 0;
        else Q <= D_next;
    end

endmodule: mem_register


module IO_register32
    (input  logic clock, reset,
     input  logic [31:0] wdata,
     input  logic [3:0]  we,
     output logic [31:0] rdata);

    logic [31:0] data_next;

    assign data_next[7:0] = (we[0]) ? wdata[7:0] : rdata[7:0];
    assign data_next[15:8] = (we[1]) ? wdata[15:8] : rdata[15:8];
    assign data_next[23:16] = (we[2]) ? wdata[23:16] : rdata[23:16];
    assign data_next[31:24] = (we[3]) ? wdata[31:24] : rdata[31:24];

    always_ff @(posedge clock, posedge reset) begin
        if (reset) rdata <= 0;
        else rdata <= data_next;
    end
endmodule: IO_register32

// WE has priority over clear
module IO_register16
    (input  logic clock, reset,
     input  logic [15:0] wdata,
     input  logic [1:0]  we,
     output logic [15:0] rdata,
     input  logic        clear);

    logic [15:0] data_next;

    assign data_next[7:0] = (we[0]) ? wdata[7:0] : (clear) ? 8'd0 : rdata[7:0];
    assign data_next[15:8] = (we[1]) ? wdata[15:8] : (clear) ? 8'd0 : rdata[15:8];

    always_ff @(posedge clock, posedge reset) begin
        if (reset) rdata <= 0;
        else rdata <= data_next;
    end
endmodule: IO_register16

/*  Create a fifo (First In First Out) with depth 4 using the given interface
 *  and constraints.
 *  -The fifo is initally empty.
 *  -Reads are combinational, so "data_out" is valid unless "empty" is asserted.
 *   Removal from the queue is processed on the clock edge.
 *  -Writes are processed on the clock edge.
 *  -If the "we" happens to be asserted while the fifo is full, do NOT update
 *   the fifo.
 *  -Similarly, if the "re" is asserted while the fifo is empty, do NOT update
 *   the fifo.
 */
module fifo(clk, rst, data_in, we, re, full, empty, data_out, size, clr);
  parameter WIDTH = 32;
  input logic clk, rst;
  input logic [WIDTH-1:0] data_in;
  input logic we; //write enable
  input logic re; //read enable
  input logic clr;
  output logic full;
  output logic empty;
  output logic [WIDTH-1:0] data_out;
  output logic [3:0] size;

  logic [WIDTH-1:0] Q [7:0]; // memory array of 7 bytes
  logic [31:0] elem0;
  logic [31:0] elem1, elem2, elem3, elem4, elem5, elem6, elem7;
  assign elem0 = Q[0];
  assign elem1 = Q[1];
  assign elem2 = Q[2];
  assign elem3 = Q[3];
  assign elem4 = Q[4];
  assign elem5 = Q[5];
  assign elem6 = Q[6];
  assign elem7 = Q[7];

  logic [2:0] getPtr, putPtr;
  assign empty = (size == 4'd0);
  assign full = (size == 4'd8);
  assign data_out = Q[getPtr];
  always_ff @(posedge clk, posedge rst) begin
      if (rst || clr) begin
          getPtr <= 0;
          putPtr <= 0;
          size <= 0;
      end else begin
          /* re && we adds and removes (if we can) */
          if (we && (!full) && re && (!empty)) begin
              Q[putPtr] <= data_in;
              putPtr <= putPtr + 1;
              getPtr <= getPtr + 1;
          end
          else if (we && (!full)) begin // put stuff in queue
              Q[putPtr] <= data_in;
              putPtr <= putPtr + 1;
              size <= size + 1;
          end
          else if (re && (!empty)) begin // read stuff out of the queue
              getPtr <= getPtr + 1;
              size <= size - 1;
          end
      end
  end

endmodule: fifo

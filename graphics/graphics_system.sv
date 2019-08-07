`include "../gba_core_defines.vh"
`include "../gba_mmio_defines.vh"
`default_nettype none

module graphics_system (
    output  logic [31:0] gfx_vram_A_addr, gfx_vram_B_addr, gfx_vram_C_addr,
    output  logic [31:0] gfx_oam_addr, gfx_palette_bg_addr, gfx_palette_obj_addr,
    output  logic [31:0] gfx_vram_A_addr2,
    input  logic [31:0] gfx_vram_A_data, gfx_vram_B_data, gfx_vram_C_data,
    input  logic [31:0] gfx_oam_data, gfx_palette_bg_data, gfx_palette_obj_data,
    input  logic [31:0] gfx_vram_A_data2,
    
	//input  logic [31:0] IO_reg_datas [`NUM_IO_REGS-1:0],
	
	input logic [31:0] DISPCNT_REG,
	input logic [31:0] DISPSTAT_REG,
	input logic [31:0] VCOUNT_REG,
	input logic [31:0] BG0CNT_REG,
	input logic [31:0] BG1CNT_REG,
	input logic [31:0] BG2CNT_REG,
	input logic [31:0] BG3CNT_REG,

	input logic [31:0] BG0HOFS_REG,
	input logic [31:0] BG0VOFS_REG,
	input logic [31:0] BG1HOFS_REG,
	input logic [31:0] BG1VOFS_REG,
	input logic [31:0] BG2HOFS_REG,
	input logic [31:0] BG2VOFS_REG,
	input logic [31:0] BG3HOFS_REG,
	input logic [31:0] BG3VOFS_REG,

	input logic [31:0] BG2PA_REG,
	input logic [31:0] BG2PB_REG,
	input logic [31:0] BG2PC_REG,
	input logic [31:0] BG2PD_REG,
	input logic [31:0] BG2X_L_REG,
	input logic [31:0] BG2X_H_REG,
	input logic [31:0] BG2Y_L_REG,
	input logic [31:0] BG2Y_H_REG,

	input logic [31:0] BG3PA_REG,
	input logic [31:0] BG3PB_REG,
	input logic [31:0] BG3PC_REG,
	input logic [31:0] BG3PD_REG,
	input logic [31:0] BG3X_L_REG,
	input logic [31:0] BG3X_H_REG,
	input logic [31:0] BG3Y_L_REG,
	input logic [31:0] BG3Y_H_REG,

	input logic [31:0] WIN0H_REG,
	input logic [31:0] WIN1H_REG,
	input logic [31:0] WIN0V_REG,
	input logic [31:0] WIN1V_REG,
	input logic [31:0] WININ_REG,
	input logic [31:0] WINOUT_REG,
	input logic [31:0] MOSAIC_REG,

	input logic [31:0] BLDCNT_REG,
	input logic [31:0] BLDALPHA_REG,
	input logic [31:0] BLDY_REG,
	
    input  logic        graphics_clock, vga_clock,
    input  logic        reset,

    output logic [7:0] vcount,
    output logic [8:0] hcount,
    output logic [3:0] VGA_R, VGA_G, VGA_B,
    output logic        VGA_HS,
    output logic        VGA_VS
    );

    //module instantiations
    logic wen, toggle;
    logic [14:0] graphics_color, vga_color;
    logic [16:0] graphics_addr, vga_addr;
    logic [14:0] buffer0_dout, buffer1_dout;
    logic [16:0] buffer0_address, buffer1_address;
    logic [14:0] buffer0_din, buffer1_din;
    logic buffer0_ce, buffer1_ce;
    logic buffer0_we, buffer1_we;


    //dbl_buffer buffers

    dbl_buffer_bram0 buf0 (.clka(vga_clock), .addra(buffer0_address), .dina(buffer0_din), .douta(buffer0_dout),
                           .ena(buffer0_ce), .wea(buffer0_we));
						   
    dbl_buffer_bram1 buf1 (.clka(vga_clock), .addra(buffer1_address), .dina(buffer1_din), .douta(buffer1_dout),
                           .ena(buffer1_ce), .wea(buffer1_we));

    //interface between graphics and dbl_buffer
    dblbuffer_driver driver(.toggle, .wen, .graphics_clock, .vcount, .hcount,
                            .graphics_addr, .clk(vga_clock), .rst_b(~reset));

    //double_buffer
    double_buffer video_buf(.ap_clk(vga_clock), .ap_rst_n(~reset),
							.graphics_addr(graphics_addr), .graphics_color(graphics_color),
							.buf_select(toggle), .vga_addr(vga_addr), .wen(wen), .vga_color(vga_color),
                            .buf0_address0(buffer0_address), .buf1_address0(buffer1_address),
                            .buf0_d0(buffer0_din), .buf1_d0(buffer1_din),
                            .buf0_q0(buffer0_dout), .buf1_q0(buffer1_dout),
                            .buf0_ce0(buffer0_ce), .buf1_ce0(buffer1_ce),
                            .buf0_we0(buffer0_we), .buf1_we0(buffer1_we));
    //vga
    vga_top video(.clock(vga_clock), .reset(reset),
						.data(vga_color),
						.addr(vga_addr), 
						.VGA_R, .VGA_G, .VGA_B,
						.VGA_HS, .VGA_VS);

    //graphics
    graphics_top gfx(.clock(graphics_clock), .reset,
                 .gfx_vram_A_data, .gfx_vram_B_data, .gfx_vram_C_data,
                 .gfx_oam_data, .gfx_palette_bg_data, .gfx_palette_obj_data,
                 .gfx_vram_A_data2,
                 .gfx_vram_A_addr, .gfx_vram_B_addr, .gfx_vram_C_addr,
                 .gfx_oam_addr, .gfx_palette_bg_addr, .gfx_palette_obj_addr,
                 .gfx_vram_A_addr2,
                 
				 //.registers(IO_reg_datas),
				 
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
				 
                 .output_color(graphics_color)
			);

endmodule: graphics_system

module dblbuffer_driver(
    output logic toggle,
    output logic wen,
    input logic graphics_clock,
    output logic [16:0] graphics_addr,
    output logic [7:0] vcount,
    output logic [8:0] hcount,
    input logic clk,
    input logic rst_b
    );

    assign vcount = row;
    assign hcount = col;

    dbdriver_counter #(20, 842687) toggler(.clk, .rst_b, .en(1'b1), .clear(1'b0), .last(toggle), .Q());

    logic [18:0] timer;
    logic [7:0] row;
    logic [8:0] col;

    logic step_row;
    logic next_frame;
    logic step;
    assign step = timer[1] & timer[0];
    dbdriver_counter #(19, 280895) sync(.clk(graphics_clock), .en(1'b1), .clear(1'b0), .rst_b, .last(next_frame), .Q(timer));
    dbdriver_counter #(16, 38399) addrs(.clk(graphics_clock), .en(wen & step), .clear(next_frame & step), .rst_b, .last(), .Q(graphics_addr));

    dbdriver_counter #(8, 227) rows(.clk(graphics_clock), .en(step_row & step), .clear(next_frame & step), .rst_b, .last(), .Q(row));
    dbdriver_counter #(9, 307) cols(.clk(graphics_clock), .en(step), .clear(next_frame & step), .rst_b, .last(step_row), .Q(col));

    assign wen = row < 8'd160 && col < 9'd240;

endmodule

module dbdriver_counter
    #(
    parameter WIDTH=18,
    parameter MAX = 210671
    )
    (
    input logic clk,
    input logic rst_b,
    input logic en,
    input logic clear,
    output logic [WIDTH-1:0] Q,
    output logic last
    );

    assign last = Q == MAX;

    logic [WIDTH-1:0] next;

    always_comb begin
        if(clear) begin
            next = 0;
        end
        else if(~en) begin
            next = Q;
        end
        else if(last) begin
            next = 0;
        end
        else begin
            next = Q + 1;
        end
    end

    always_ff @(posedge clk, negedge rst_b) begin
        if(~rst_b) begin
            Q <= 0;
        end
        else begin
            Q <= next;
        end
    end
endmodule

`default_nettype wire

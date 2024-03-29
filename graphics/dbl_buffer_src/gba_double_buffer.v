// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.2
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="gba_double_buffer,hls_ip_2016_2,{HLS_INPUT_TYPE=c,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=1,HLS_INPUT_PART=xc7z020clg484-1,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=pipeline,HLS_SYN_CLOCK=4.281000,HLS_SYN_LAT=1,HLS_SYN_TPT=1,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=4,HLS_SYN_LUT=54}" *)

module gba_double_buffer (
        ap_clk,
        ap_rst_n,
        graphics_color,
        vga_color,
        graphics_addr,
        vga_addr,
        buf0_address0,
        buf0_ce0,
        buf0_we0,
        buf0_d0,
        buf0_q0,
        buf1_address0,
        buf1_ce0,
        buf1_we0,
        buf1_d0,
        buf1_q0,
        wen,
        buf_select
);

parameter    ap_ST_pp0_stg0_fsm_0 = 1'b1;
parameter    ap_const_lv32_0 = 32'b00000000000000000000000000000000;

input   ap_clk;
input   ap_rst_n;
input  [14:0] graphics_color;
output  [14:0] vga_color;
input  [16:0] graphics_addr;
input  [16:0] vga_addr;
output  [16:0] buf0_address0;
output   buf0_ce0;
output   buf0_we0;
output  [14:0] buf0_d0;
input  [14:0] buf0_q0;
output  [16:0] buf1_address0;
output   buf1_ce0;
output   buf1_we0;
output  [14:0] buf1_d0;
input  [14:0] buf1_q0;
input  [0:0] wen;
input  [0:0] buf_select;

reg[16:0] buf0_address0;
reg buf0_ce0;
reg buf0_we0;
reg[16:0] buf1_address0;
reg buf1_ce0;
reg buf1_we0;

reg    ap_rst_n_inv;
wire   [0:0] buf_select_read_read_fu_56_p2;
reg   [0:0] buf_select_read_reg_191;
(* fsm_encoding = "none" *) reg   [0:0] ap_CS_fsm;
reg    ap_sig_cseq_ST_pp0_stg0_fsm_0;
reg    ap_sig_41;
reg    ap_reg_ppiten_pp0_it1;
wire   [0:0] wen_read_read_fu_62_p2;
reg   [0:0] wen_read_reg_195;
wire   [14:0] ap_reg_phiprechg_storemerge2_reg_151pp0_it1;
reg   [14:0] storemerge2_phi_fu_154_p8;
wire   [63:0] tmp_4_fu_169_p1;
wire   [63:0] tmp_fu_175_p1;
wire   [63:0] tmp_3_fu_181_p1;
wire   [63:0] tmp_1_fu_186_p1;
reg   [0:0] ap_NS_fsm;
wire    ap_sig_pprstidle_pp0;
reg    ap_sig_55;
reg    ap_sig_65;
reg    ap_sig_69;
reg    ap_sig_89;
reg    ap_sig_60;

// power-on initialization
initial begin
#0 ap_CS_fsm = 1'b1;
#0 ap_reg_ppiten_pp0_it1 = 1'b0;
end

always @ (posedge ap_rst_n_inv or posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_CS_fsm <= ap_ST_pp0_stg0_fsm_0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_rst_n_inv or posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_reg_ppiten_pp0_it1 <= 1'b0;
    end else begin
        if ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0)) begin
            ap_reg_ppiten_pp0_it1 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0)) begin
        buf_select_read_reg_191 <= buf_select;
        wen_read_reg_195 <= wen;
    end
end

always @ (*) begin
    if (ap_sig_41) begin
        ap_sig_cseq_ST_pp0_stg0_fsm_0 = 1'b1;
    end else begin
        ap_sig_cseq_ST_pp0_stg0_fsm_0 = 1'b0;
    end
end

assign ap_sig_pprstidle_pp0 = 1'b0;

always @ (*) begin
    if (ap_sig_89) begin
        if (ap_sig_69) begin
            buf0_address0 = tmp_fu_175_p1;
        end else if (ap_sig_65) begin
            buf0_address0 = tmp_3_fu_181_p1;
        end else if (ap_sig_55) begin
            buf0_address0 = tmp_4_fu_169_p1;
        end else begin
            buf0_address0 = 'bx;
        end
    end else begin
        buf0_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & (wen_read_read_fu_62_p2 == 1'b0) & (buf_select_read_read_fu_56_p2 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & (buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & ~(buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0)))) begin
        buf0_ce0 = 1'b1;
    end else begin
        buf0_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & ~(buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0))) begin
        buf0_we0 = 1'b1;
    end else begin
        buf0_we0 = 1'b0;
    end
end

always @ (*) begin
    if (ap_sig_89) begin
        if (ap_sig_65) begin
            buf1_address0 = tmp_fu_175_p1;
        end else if (ap_sig_69) begin
            buf1_address0 = tmp_1_fu_186_p1;
        end else if (ap_sig_60) begin
            buf1_address0 = tmp_4_fu_169_p1;
        end else begin
            buf1_address0 = 'bx;
        end
    end else begin
        buf1_address0 = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & (wen_read_read_fu_62_p2 == 1'b0) & ~(buf_select_read_read_fu_56_p2 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & (buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & ~(buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0)))) begin
        buf1_ce0 = 1'b1;
    end else begin
        buf1_ce0 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1) & (buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0))) begin
        buf1_we0 = 1'b1;
    end else begin
        buf1_we0 = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it1) & ~(wen_read_reg_195 == 1'b0) & ~(buf_select_read_reg_191 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it1) & (wen_read_reg_195 == 1'b0) & ~(buf_select_read_reg_191 == 1'b0)))) begin
        storemerge2_phi_fu_154_p8 = buf1_q0;
    end else if ((((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it1) & ~(wen_read_reg_195 == 1'b0) & (buf_select_read_reg_191 == 1'b0)) | ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == ap_reg_ppiten_pp0_it1) & (wen_read_reg_195 == 1'b0) & (buf_select_read_reg_191 == 1'b0)))) begin
        storemerge2_phi_fu_154_p8 = buf0_q0;
    end else begin
        storemerge2_phi_fu_154_p8 = ap_reg_phiprechg_storemerge2_reg_151pp0_it1;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_pp0_stg0_fsm_0 : begin
            ap_NS_fsm = ap_ST_pp0_stg0_fsm_0;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_reg_phiprechg_storemerge2_reg_151pp0_it1 = 'bx;

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

always @ (*) begin
    ap_sig_41 = (ap_CS_fsm[ap_const_lv32_0] == 1'b1);
end

always @ (*) begin
    ap_sig_55 = ((wen_read_read_fu_62_p2 == 1'b0) & (buf_select_read_read_fu_56_p2 == 1'b0));
end

always @ (*) begin
    ap_sig_60 = ((wen_read_read_fu_62_p2 == 1'b0) & ~(buf_select_read_read_fu_56_p2 == 1'b0));
end

always @ (*) begin
    ap_sig_65 = ((buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0));
end

always @ (*) begin
    ap_sig_69 = (~(buf_select_read_read_fu_56_p2 == 1'b0) & ~(wen_read_read_fu_62_p2 == 1'b0));
end

always @ (*) begin
    ap_sig_89 = ((1'b1 == ap_sig_cseq_ST_pp0_stg0_fsm_0) & (1'b1 == 1'b1));
end

assign buf0_d0 = graphics_color;

assign buf1_d0 = graphics_color;

assign buf_select_read_read_fu_56_p2 = buf_select;

assign tmp_1_fu_186_p1 = vga_addr;

assign tmp_3_fu_181_p1 = vga_addr;

assign tmp_4_fu_169_p1 = vga_addr;

assign tmp_fu_175_p1 = graphics_addr;

assign vga_color = storemerge2_phi_fu_154_p8;

assign wen_read_read_fu_62_p2 = wen;

endmodule //gba_double_buffer

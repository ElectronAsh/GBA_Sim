module bg_rot_scale_top
    (input logic [27:0] bg2x, bg2y, bg3x, bg3y,
     input logic [15:0] bg2pa, bg2pb, bg2pc, bg2pd,
     input logic [15:0] bg3pa, bg3pb, bg3pc, bg3pd,
     input logic [1:0] bgno,
     input logic steprow, newframe,
     input logic clock, rst_b,
     output logic [9:0] x, y,
     output logic overflow);

    logic [9:0] x2, y2, x3, y3;
    logic overflow2, overflow3;

    bg_rot_scale_unit bg2rot(.A(bg2pa), .B(bg2pb), .C(bg2pc), .D(bg2pd), .bgx(bg2x), .bgy(bg2y), .step(bgno == 2'd2), .steprow, .newframe, .clock, .rst_b, .x(x2), .y(y2), .overflow(overflow2));
    bg_rot_scale_unit bg3rot(.A(bg3pa), .B(bg3pb), .C(bg3pc), .D(bg3pd), .bgx(bg3x), .bgy(bg3y), .step(bgno == 2'd3), .steprow, .newframe, .clock, .rst_b, .x(x3), .y(y3), .overflow(overflow3));

    assign x = bgno[0] ? x3 : x2;
    assign y = bgno[0] ? y3 : y2;
    assign overflow = bgno[1] ? overflow3 : overflow2;

endmodule: bg_rot_scale_top

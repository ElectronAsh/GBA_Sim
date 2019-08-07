module bg_mux_4_to_1
  #(parameter width=16)
  (output logic [width-1:0] y,
   input logic [width-1:0] i0,
   input logic [width-1:0] i1,
   input logic [width-1:0] i2,
   input logic [width-1:0] i3,
   input logic [1:0] s);

  always_comb begin
    case(s)
      2'd0: y = i0;
      2'd1: y = i1;
      2'd2: y = i2;
      2'd3: y = i3;
    endcase
  end

endmodule: bg_mux_4_to_1

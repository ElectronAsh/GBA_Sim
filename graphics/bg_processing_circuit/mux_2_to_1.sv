module mux_2_to_1
  #(parameter width=4)
  (output logic [width-1:0] y,
  input logic [width-1:0] i0, i1,
  input logic s);

  assign y = s ? i1 : i0;

endmodule: mux_2_to_1

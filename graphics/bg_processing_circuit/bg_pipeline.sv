module bg_pipeline
  #(parameter WIDTH)
  (input logic [WIDTH-1:0] d,
   output logic [WIDTH-1:0] q,
   input logic clock);

  always_ff @(posedge clock)
    q <= d;

endmodule: bg_pipeline

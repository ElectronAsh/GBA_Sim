module counter
  #(parameter width=4)
  (output logic [width-1:0] q,
  input logic [width-1:0] d,
  input logic clk, enable, clear, load, up, rst_b);

  logic [width-1:0] ns;

  always_ff @(posedge clk, negedge rst_b)
    if(~rst_b)
      q <= 0;
    else
      q <= ns;

  always_comb begin
    if(clear)
      ns = 'b0;
    else if(load)
      ns = d;
    else if(enable)
      ns = up ? q + 1 : q - 1;
    else
      ns = q;
  end

endmodule: counter

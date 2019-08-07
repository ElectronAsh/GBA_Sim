module pe_register(q, d, clk, clear, enable, rst_b);

   parameter
            width = 32;

   output logic [(width-1):0] q;
   input logic [(width-1):0]  d;
   input logic clk, clear, enable, rst_b;

   always @(posedge clk or negedge rst_b)
     if (~rst_b)
       q <= 0;
     else if (clear)
       q <= 0;
     else if (enable)
       q <= d;

endmodule: pe_register

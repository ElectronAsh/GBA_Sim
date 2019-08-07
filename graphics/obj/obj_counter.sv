module obj_counter #(parameter WIDTH = 8) (
    input  logic clock, reset,
    output logic [WIDTH-1:0] q,
    input  logic en, clear);

    always_ff @(posedge clock, posedge reset) begin
        if (reset) q <= {WIDTH{1'b0}};
        else if (clear) q <= {WIDTH{1'b0}};
        else if (en) q <= q + 1;
    end
endmodule: obj_counter

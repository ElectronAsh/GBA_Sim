module within_preimage_checker (
    output logic        valid,
    input  logic [5:0] X, Y,
    input  logic [6:0] hsize, vsize);

    assign valid = ({1'b0, X} < hsize) & ({1'b0, Y} < vsize);

endmodule: within_preimage_checker

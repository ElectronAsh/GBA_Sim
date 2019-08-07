module row_visible_unit (
    output logic       visible,
    input  logic [7:0] row, objy,
    input  logic [7:0] vsize);

    logic [7:0] lowerbound, upperbound;
    logic [7:0] adjust_objy;

    //assign lowerbound = rotation ? objy - vsize[7:1] : objy;
    assign lowerbound = objy;
    assign upperbound = lowerbound + vsize;
    assign visible = (row < upperbound) & ((objy[7] & ~upperbound[7]) | (lowerbound <= row));

endmodule: row_visible_unit

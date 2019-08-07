module dbl_buffer_bram1 (
	input logic clka,
	input logic wea,
	input logic ena,
	input logic dina,
    input logic [13:0] addra,
    output logic [31:0] douta
);

    logic [31:0] mem [16383:0];
	
always_ff @(posedge clka) begin
	if (ena & wea) mem[addra] <= dina;
end

assign douta = mem[addra];

endmodule: dbl_buffer_bram1

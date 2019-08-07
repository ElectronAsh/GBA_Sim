module OAM (
	input logic rsta,
	input logic clka,
	input logic wea,
	input logic dina,
    input logic [13:0] addra,
    output logic [31:0] douta,
	
	input logic rstb,
	input logic clkb,
	input logic web,
	input logic dinb,
    input logic [13:0] addrb,
    output logic [31:0] doutb
);

    logic [31:0] mem [16383:0];
	
	/*
    initial begin
        $readmemh("vram_a_sim.txt", OAM);
    end
	*/
always_ff @(posedge clka)
/*
if (rsta) begin

end
else*/ begin
	if (wea) mem[addra] <= dina;
	
	if (web) mem[addrb] <= dinb;
	
	//$display("data=%h addr=%h word=%h",data, addr, addr[31:2]);
end

assign douta = mem[addra];
assign doutb = mem[addrb];

endmodule: OAM

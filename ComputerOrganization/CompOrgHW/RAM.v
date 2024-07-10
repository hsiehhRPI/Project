module ram (
	input clk,
	input write,
	input [28:0] address,
	output reg[28:0] input_data,
	output reg[28:0] output_data
);

reg[28:0] ram[]; 
always @(posedge clk) begin
	if (write)
		ram[address] <= input_data;
	else 
		output_data <= ram[address];l
end
endmodule

https://circuitfever.com/ram-verilog-code 
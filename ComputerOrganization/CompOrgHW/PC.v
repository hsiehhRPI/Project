module PC (clk, reset, counter, haltrue);
input clk, 
output counter;
always@(posedge clk) begin
	if (reset)	
		counter <= 0;			//Reset 
	else if (haltrue)
		counter <= counter;
	else 
		counter <= counter + 1;
end 
endmodule

Reference:
https://www.geeksforgeeks.org/counter-design-using-verilog-hdl/
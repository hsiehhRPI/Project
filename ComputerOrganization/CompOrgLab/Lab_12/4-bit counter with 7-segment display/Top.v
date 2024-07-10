module Top(clk, rst, enable, upDown, count, seg7);
// count[3:0] output included for convenience in debug and testbenches
	input clk, rst, enable, upDown;
	output [3:0] count;
	output [6:0] seg7;
	
   wire clkCounter;  // divided clock for Counter module
	
	// Add code here to instantiate and connect the three modules together structurally
	ClkDiv ClkDiv_1(clk, clkOut);
	Count4 Count4_1(clkOut,rst,enable,upDown, count);
	Seg7Decode Seg7Decode_1(count, seg7);

endmodule

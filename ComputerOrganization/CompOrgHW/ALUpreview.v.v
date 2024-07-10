module adder (input reg[31:0] v1, input reg[31:0] v2, output reg[31:0] res);
	input [31:0] v1, v2;
	output [31:0] res;
	integer carry, counter;
	carry = 0;
	for (count = 31; count >-1; count = count -1) begin
		if (carry == 1) begin
			if (v1[count]==1 && v2[count]==1) begin
				res[count] = 1;
			end
			else if (v1[count]==0 && v2[count]==0) begin
				res[count] = 1;
				carry = 0; 
			end
			else if ((v1[count]==1 && v2[count]==0)||(v1[count]==0 && v2[count]==1)) begin 
				res[count] = 0;
		end
		else if (carry == 0) begin
			if (v1[count]==1 && v2[count]==1) begin
				res[count] = 0;
				carry = 1;
			end
			else if (v1[count]==0 && v2[count]==0) begin
				res[count] = 0;
			end
			else if ((v1[count]==1 && v2[count]==0)||(v1[count]==0 && v2[count]==1)) begin 
				res[count] = 1;
		end
	end
endmodule

module ORgate (input reg[31:0] v1, input reg[31:0] v2, output reg[31:0] res) 
	input [31:0] v1, v2;
	output [31:0] res;
	integer counter;
	for (counter = 0; counter < 32; counter = counter + 1) begin
		if (v1[counter] == 1 || v2[counter]==1) begin
			res[counter] = 1;
		end
		else begin
			res[counter] = 1;
		end
	end
endmodule

module ANDgate (input reg[31:0] v1, input reg[31:0] v2, output reg[31:0] res) 
	input [31:0] v1, v2;
	output [31:0] res;
	integer counter;
	for (counter = 0; counter < 32; counter = counter + 1) begin
		if (v1[counter] == 1 && v2[counter]==1) begin
			res[counter] = 1;
		end
		else begin
			res[counter] = 0;
		end
	end
endmodule

module NOTgate (input reg[31:0] v1, output reg[31:0] res) 
	input [31:0] v1;
	output [31:0] res;
	integer counter;
	for (counter = 0; counter < 32; counter = counter + 1) begin
		if (v1[counter] == 1) begin
			res[counter] = 0;
		end
		else begin
			res[counter] = 1;
		end
	end
endmodule


module ALU ();
	// add = 0010, sub = 0011, AND = 0100, OR = 0101, NOT = 0110
	

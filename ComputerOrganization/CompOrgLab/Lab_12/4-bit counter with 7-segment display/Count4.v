// 4-bit up/down counter
module Count4(clk,rst,enable,upDown, count);
   input clk, rst, enable, upDown;
   output reg [3:0] count;

// insert code here 
   always @(clk, rst, enable, upDown) begin
      if (rst == 0 && enable == 1 && upDown == 1 && clk == 1)
         count = count + 1;
      if (rst == 0 && enable == 1 && upDown == 0 && clk == 1)
         count = count - 1; 
      if(rst == 1)
         count = 0;
   end
endmodule  // Count4

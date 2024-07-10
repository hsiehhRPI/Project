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


`timescale 1ns/1ns
//our 32-bit ALU
module ALU(opcode, MBR, addr, AC, state);
    //defining the opcodes
    parameter Add = 4'b0000,
            Subt = 4'b0001, 
            And = 4'b0010,
            Or = 4'b0011,
            Not = 4'b0100, 
            Halt = 4'b0101, 
            Load = 4'b0110, 
            Store = 4'b0111, 
            Clear = 4'b1000, 
            Skip = 4'b1001, 
            Jump = 4'b1010, 
            Jal = 4'b1011, 
            Return = 4'b1100;
    
    input [2:0] state;
    input [3:0] opcode;
    input [31:0] MBR;
  output reg [31:0] AC = 0; //the accumulator 
    input [27:0] addr;
    reg [31:0] negMBR;// the 2's complement notation of MBR

    always @ (state) begin //updated to only go once every clock cycle
        if(state == 2) begin
            negMBR = ~MBR + 1;
            case (opcode)
                Load:
                   AC =  MBR; 
                Clear:
                    AC = 0;
                And:
                    AC = AC & MBR;
                Not:
                    AC = ~AC;
                Jal:
                    AC= addr + 1;
                Add:
                    AC = AC + MBR;
                Subt:
                    AC = AC + negMBR;         
            endcase
        end// end if block
    end// end always
endmodule

// Code your design here
module CPU(input clock);
   
   parameter Add = 4'b0000,
            Subt = 4'b0001, 
            And = 4'b0010,
            Or = 4'b0011,
            Not = 4'b0100, 
            Halt = 4'b0101, 
            Load = 4'b0110, 
            Store = 4'b0111, 
            Clear = 4'b1000, 
            Skip = 4'b1001, 
            Jump = 4'b1010, 
            Jal = 4'b1011, 
            Return = 4'b1100;

   //variables
   reg [1:0] state; //state program is in: fetch, decode, execute instructions
   reg [31:0] PC;
   reg [31:0] IR;
   reg [3:0] opcode = 0000;
   reg [27:0] MAR;
   wire [31:0] AC = 8'h00000000;
   reg [31:0] MBR;


   //stuff for memory
   reg [27:0] mem_addy;
   reg [31:0] write_val; // the value used to write to mem
   wire [31:0] read_val; 
   reg Mem_RW;
   reg Mem_done;
   

   //initial starting conditions
   state = 0;
   PC = -1;

   //make the Control_Unit module
   //Control_Unit CU(PC, IR, Memory, state); //we need to make sure this only runs on every clock cycle as well, right?
   //make memory
   Main_Memory Mem( mem_addy, mem_val, Mem_RW, Mem_done);

   
   //run program (loop: read line of code, put into IR, run on ALU, go to next line of code)
   always @ (posedge clock) begin
      case (state)
         0: begin //fetch--read line of code and put into IR
            if( opcode != Halt){
               PC = PC + 4;
            }
            //IR = MEM[PC]
            mem_addy = PC;
            mem_RW = 1;
            mem_done = 0;
            #10; //wait a min to get the contents into the read value
            mem_done = 1;
            IR = read_val;
            opcode = [31:28]IR;
            if( opcode != Halt)
               state = 1;
         end
         1: begin //decode--get opcode vs instruction
            //finish all pre-ALU instructions here, now that we have the opcode
            MAR = [27:0]IR; //MAR <- X
            if (opcode == Add | opcode = Load | opcode = Subt | opcode = And | opcode = Or ) begin
               //MBR <- M[MAR]
               mem_addy = MAR;
               mem_RW = 1; //read
               mem_done = 0;//triggers the read in the memory module
               #10;
               mem_done = 1;//done reading
               MBR = read_val;
            end
            else if ( opcode == Skip) begin
               PC = PC + 4
            end
            else if( opcode == JAL) begin
               //MBR <- PC + 
               MBR = PC + 4;
               //M[MAR] <- MBR #stores value in MBR to address of MAR
               mem_addy = MAR;
               write_val = MBR;
               mem_RW = 0; // write
               mem_done = 0; //triggers the write
               #10; //let the write happen
               mem_done = 1;
            end
            else if (opcode == Return) begin
               //MBR <- M[MAR]
               mem_addy = MAR;
               mem_RW = 1; // read
               mem_done = 0; //triggers the read
               #10; //let the read happen
               mem_done = 1
               MBR = read_val;
               //MAR <- MBR
               MAR = [31:4]MBR;
               //MBR <- M[MAR]  # fetches the value at the address into MBR
               mem_addy = MAR;
               mem_RW = 1; // read
               mem_done = 0; //triggers the read
               #10; //let the read happen
               mem_done = 1;
               MBR = read_val;
               //PC <- MBR
               PC = MBR;
            end
            //once our pre-alu instructions are done, advance to the next state
            state = 2;
         end
         2: begin //execute--send to ALU
            #10 // giving the ALU time to do its things
            state = 3; 
         end
         
         3: begin 
            //all post-ALU instructions go here
            if (opcode = Store) begin
               //MBR <- AC
                MBR = AC;
               //M[MAR] <- MBR
               mem_addy = MAR;
               write_val = MBR;
               mem_RW = 0;//write to mem
               mem_done = 0;//trigger write
               #10;// wait for write to finish
               mem_done = 1;
            end   
            else if( opcode == Jal)
               PC = AC 
            state = 0; //for now, go back to read next line of code, we'll need something to end it
         end 
      endcase
   end

  module Main_Memory( address, writevalue, readvalue, RW, done)
  parameter mebibyte = 2**20,
    memory_bytes = (256*mebibyte) - 1;
  //inputs and outputs
  input RW;// read = 1, write = 0
  input [27:0] address;
  input [31:0] writevalue; // a value to be  written to mem
  output [31:0] readvalue; //a value to be read out to cpu
  input done;

  //Instantiate 4 chips of size 256Mi x 8
   reg [7:0] Memory1[0:memory_bytes]; 
   reg [7:0] Memory2[0:memory_bytes]; 
   reg [7:0] Memory3[0:memory_bytes]; 
   reg [7:0] Memory4[0:memory_bytes];

  //Initial datas: 
  //0
  Memory1[0000000000000000000000000000] = 8'b00000000;
  Memory2[0000000000000000000000000000] = 8'b00000000;
  Memory3[0000000000000000000000000000] = 8'b00000000;
  Memory4[0000000000000000000000000000] = 8'b00000000;
  //1, f1, set to f1 term
  Memory1[0000000000000000000000000100] = 8'b00000000; 
  Memory2[0000000000000000000000000100] = 8'b00000000;
  Memory3[0000000000000000000000000100] = 8'b00000000;
  Memory4[0000000000000000000000000100] = 8'b00000001;
  //2, initial starting index
  Memory1[0000000000000000000000001000] = 8'b00000000; 
  Memory2[0000000000000000000000001000] = 8'b00000000;
  Memory3[0000000000000000000000001000] = 8'b00000000;
  Memory4[0000000000000000000000001000] = 8'b00000010;
  //11, the last term we need to compute(for checking whether the last term)
  Memory1[0000000000000000000000001100] = 8'b00000000; 
  Memory2[0000000000000000000000001100] = 8'b00000000;
  Memory3[0000000000000000000000001100] = 8'b00000000;
  Memory4[0000000000000000000000001100] = 8'b00001011;
  //Needed Registers here
  //t0, initialized to zero for now
  Memory1[0000000000000000000000010000] = 8'b00000000; 
  Memory2[0000000000000000000000010000] = 8'b00000000;
  Memory3[0000000000000000000000010000] = 8'b00000000;
  Memory4[0000000000000000000000010000] = 8'b00000000;
  //t1, initialized to zero for now
  Memory1[0000000000000000000000010100] = 8'b00000000; 
  Memory2[0000000000000000000000010100] = 8'b00000000;
  Memory3[0000000000000000000000010100] = 8'b00000000;
  Memory4[0000000000000000000000010100] = 8'b00000000;
  //t2, initialized to zero for now
  Memory1[0000000000000000000000011000] = 8'b00000000; 
  Memory2[0000000000000000000000011000] = 8'b00000000;
  Memory3[0000000000000000000000011000] = 8'b00000000;
  Memory4[0000000000000000000000011000] = 8'b00000000;
  //t3, initialized to zero for now
  Memory1[0000000000000000000000100000] = 8'b00000000; 
  Memory2[0000000000000000000000100000] = 8'b00000000;
  Memory3[0000000000000000000000100000] = 8'b00000000;
  Memory4[0000000000000000000000100000] = 8'b00000000;
  //t4, initialized to zero for now
  Memory1[0000000000000000000000100100] = 8'b00000000; 
  Memory2[0000000000000000000000100100] = 8'b00000000;
  Memory3[0000000000000000000000100100] = 8'b00000000;
  Memory4[0000000000000000000000100100] = 8'b00000000;

//--------------------PROGRAM LINES START HERE---------------------------

  //Hard coded instruction lines into the memory
  //MAR = 0000 0001, AC=MBR=1    Load info from MAR into MBR then to AC
  Memory1[0000000000000000000000101000] = 8'b01100000;
  Memory2[0000000000000000000000101000] = 8'b00000000;
  Memory3[0000000000000000000000101000] = 8'b00000000;
  Memory4[0000000000000000000000101000] = 8'b00000100;
  //MAR = address of t0, MBR=AC=1, t0 = 1 Put f1 term into t0
  Memory1[0000000000000000000000101100] = 8'b01110000;
  Memory2[0000000000000000000000101100] = 8'b00000000;
  Memory3[0000000000000000000000101100] = 8'b00000000;
  Memory4[0000000000000000000000101100] = 8'b00010000;
  //MAR = address of t1, MBR=AC=1, t1 = 1 Put f2 term into t1
  Memory1[0000000000000000000000110000] = 8'b01110000;
  Memory2[0000000000000000000000110000] = 8'b00000000;
  Memory3[0000000000000000000000110000] = 8'b00000000;
  Memory4[0000000000000000000000110000] = 8'b00010100;
  //Clear AC
  Memory1[0000000000000000000000110100] = 8'b10000000;
  Memory2[0000000000000000000000110100] = 8'b00000000;
  Memory3[0000000000000000000000110100] = 8'b00000000;
  Memory4[0000000000000000000000110100] = 8'b00000000;
  //AC = 0, MAR = address of t2, MBR = AC = 0, t2 = 0 (This is the fibonacci term)
  Memory1[0000000000000000000000111000] = 8'b01110000;
  Memory2[0000000000000000000000111000] = 8'b00000000;
  Memory3[0000000000000000000000111000] = 8'b00000000;
  Memory4[0000000000000000000000111000] = 8'b00011000;
  //MAR = address of 2 the number, AC=MBR=2, load 2 to AC
  Memory1[0000000000000000000000111100] = 8'b01100000;
  Memory2[0000000000000000000000111100] = 8'b00000000;
  Memory3[0000000000000000000000111100] = 8'b00000000;
  Memory4[0000000000000000000000111100] = 8'b00001000;
  //MAR = address of t3, MBR=AC=2, t3 = 2, (store 2 into t3, for start index of loop)
  Memory1[0000000000000000000001000000] = 8'b01110000;
  Memory2[0000000000000000000001000000] = 8'b00000000;
  Memory3[0000000000000000000001000000] = 8'b00000000;
  Memory4[0000000000000000000001000000] = 8'b00011100;
  //MAR = address of 11 the number, AC=MBR=11
  Memory1[0000000000000000000001000100] = 8'b01100000;
  Memory2[0000000000000000000001000100] = 8'b00000000;
  Memory3[0000000000000000000001000100] = 8'b00000000;
  Memory4[0000000000000000000001000100] = 8'b00001100;
  //MAR = address of t4, MBR = AC = t4 = 11 (store 2 into t3, for end index of loop)
  Memory1[0000000000000000000001001000] = 8'b01110000;
  Memory2[0000000000000000000001001000] = 8'b00000000;
  Memory3[0000000000000000000001001000] = 8'b00000000;
  Memory4[0000000000000000000001001000] = 8'b00100000;
  //--------------Loop starts here----------------------------
  //MAR = address of t0, AC=MBR=t0=1 (since f1 = f(n-2) = 1)
  Memory1[0000000000000000000001001100] = 8'b01100000;
  Memory2[0000000000000000000001001100] = 8'b00000000;
  Memory3[0000000000000000000001001100] = 8'b00000000;
  Memory4[0000000000000000000001001100] = 8'b00010000;
  //MAR = address of t1, MBR=t1, AC = AC+MBR = t0+t1 = 2 (computes f3 term)
  Memory1[0000000000000000000001010000] = 8'b00000000;
  Memory2[0000000000000000000001010000] = 8'b00000000;
  Memory3[0000000000000000000001010000] = 8'b00000000;
  Memory4[0000000000000000000001010000] = 8'b00010100;
  //Store the value into t2, which holds our computed fibonacci number
  Memory1[0000000000000000000001010100] = 8'b01110000;
  Memory2[0000000000000000000001010100] = 8'b00000000;
  Memory3[0000000000000000000001010100] = 8'b00000000;
  Memory4[0000000000000000000001010100] = 8'b00011000;
  //MAR = address of t1, AC=MBR=t1
  Memory1[0000000000000000000001011000] = 8'b01100000;
  Memory2[0000000000000000000001011000] = 8'b00000000;
  Memory3[0000000000000000000001011000] = 8'b00000000;
  Memory4[0000000000000000000001011000] = 8'b00010100;
  //MAR = address of t0, t0 = AC = MBR = t1
  //(move content in t1 into t0, f(n-1) became the f(n-2) for the next calculation)
  Memory1[0000000000000000000001011100] = 8'b01110000;
  Memory2[0000000000000000000001011100] = 8'b00000000;
  Memory3[0000000000000000000001011100] = 8'b00000000;
  Memory4[0000000000000000000001011100] = 8'b00010000;
  //MAR = address of t2, AC=MBR=t2
  Memory1[0000000000000000000001100000] = 8'b01100000;
  Memory2[0000000000000000000001100000] = 8'b00000000;
  Memory3[0000000000000000000001100000] = 8'b00000000;
  Memory4[0000000000000000000001100000] = 8'b00011000;
   //MAR = address of t1, t1 = AC = MBR = t2
  //(move content in t2 into t1, current fibonacci number became the f(n-1) for the next calculation)
  Memory1[0000000000000000000001100100] = 8'b01110000;
  Memory2[0000000000000000000001100100] = 8'b00000000;
  Memory3[0000000000000000000001100100] = 8'b00000000;
  Memory4[0000000000000000000001100100] = 8'b00010100;
  //MAR = address of t3, AC=MBR=t3
  Memory1[0000000000000000000001101000] = 8'b01100000;
  Memory2[0000000000000000000001101000] = 8'b00000000;
  Memory3[0000000000000000000001101000] = 8'b00000000;
  Memory4[0000000000000000000001101000] = 8'b00011100;
  //MAR = address of 1(the number), MBR=1, AC = AC+1 = t3+1(calculate incrementation)  
  Memory1[0000000000000000000001101100] = 8'b00000000;
  Memory2[0000000000000000000001101100] = 8'b00000000;
  Memory3[0000000000000000000001101100] = 8'b00000000;
  Memory4[0000000000000000000001101100] = 8'b00000100;
  //MAR = address of t3, MBR = AC = t3 = t3+1 (update the index with incremented index)
  Memory1[0000000000000000000001110000] = 8'b01110000;
  Memory2[0000000000000000000001110000] = 8'b00000000;
  Memory3[0000000000000000000001110000] = 8'b00000000;
  Memory4[0000000000000000000001110000] = 8'b00011100;
  //MAR = address of t3, AC=MBR=t3
  Memory1[0000000000000000000001110100] = 8'b01100000;
  Memory2[0000000000000000000001110100] = 8'b00000000;
  Memory3[0000000000000000000001110100] = 8'b00000000;
  Memory4[0000000000000000000001110100] = 8'b00011100;
  //MAR = address of t4, MBR = t4. AC = AC-MBR = t3-t4 (to check whether t3 = t4)
  Memory1[0000000000000000000001111000] = 8'b00010000;
  Memory2[0000000000000000000001111000] = 8'b00000000;
  Memory3[0000000000000000000001111000] = 8'b00000000;
  Memory4[0000000000000000000001111000] = 8'b00100000;
  //MAR = address of t4, MBR = t4. AC = AC-MBR = t3-t4 (if t3 = t4 = 11, skip to halt)
  //I'm not sure if this line is right
  Memory1[0000000000000000000001111100] = 8'b10010000;
  Memory2[0000000000000000000001111100] = 8'b00000000;
  Memory3[0000000000000000000001111100] = 8'b00000000;
  Memory4[0000000000000000000001111100] = 8'b00001000;
  //Jump to loop tag
  Memory1[0000000000000000000010000000] = 8'b10010000;
  Memory2[0000000000000000000010000000] = 8'b00000000;
  Memory3[0000000000000000000010000000] = 8'b00000000;
  Memory4[0000000000000000000010000000] = 8'b01001100;
  //AC=MBR=t2(f11), use $display to check testbench
  Memory1[0000000000000000000010000100] = 8'b01100000;
  Memory2[0000000000000000000010000100] = 8'b00000000;
  Memory3[0000000000000000000010000100] = 8'b00000000;
  Memory4[0000000000000000000010000100] = 8'b00110000;
  //Stop PC from incrementing, stops program from continue 
  Memory1[0000000000000000000010001000] = 8'b01010000;
  Memory2[0000000000000000000010001000] = 8'b00000000;
  Memory3[0000000000000000000010001000] = 8'b00000000;
  Memory4[0000000000000000000010001000] = 8'b00000000;

  always @(negedge done) begin //when the done is set to 0, we do a read/write
      if(RW == 1'b1) // read
           begin 
             readvalue[31:24] = Memory1[address];
             readvalue[23:16] = Memory2[address];
             readvalue[15:8] = Memory3[address];
             readvalue[7:0] = Memory4[address];
           end
      else if (RW == 1'b0) // write
           begin 
            //Separate MBR's content into 4 pieces to fit the architecture and write to correct memory areas of MAR
             Memory1[address] = writevalue[31:24];
             Memory2[address] = writevalue[23:16];
             Memory3[address] = writevalue[15:8];
             Memory4[address] = writevalue[7:0];
           end
    //set DONE to true
    done = 1;
  end
endmodule


  /*
  reg [memory_bytes:0] Memory1[0:7]; 
  reg [memory_bytes:0] Memory2[0:7]; 
  reg [memory_bytes:0] Memory3[0:7]; 
  reg [memory_bytes:0] Memory4[0:7]; 
  
  Memory1[0000000000000000000000000000] = 8'b00000000;
  Memory2[0000000000000000000000000000] = 8'b00000000;
  Memory3[0000000000000000000000000000] = 8'b00000000;
  Memory4[0000000000000000000000000000] = 8'b00000000;*/

  
/*
  //Initial datas: 
  //0
  Memory1[0000000000000000000000000000] = 8'b00000000;
  Memory2[0000000000000000000000000000] = 8'b00000000;
  Memory3[0000000000000000000000000000] = 8'b00000000;
  Memory4[0000000000000000000000000000] = 8'b00000000;
  //1, f1, set to f1 term
  Memory1[0000000000000000000000000100] = 8'b00000000; 
  Memory2[0000000000000000000000000100] = 8'b00000000;
  Memory3[0000000000000000000000000100] = 8'b00000000;
  Memory4[0000000000000000000000000100] = 8'b00000001;
  //2, initial starting index
  Memory1[0000000000000000000000001000] = 8'b00000000; 
  Memory2[0000000000000000000000001000] = 8'b00000000;
  Memory3[0000000000000000000000001000] = 8'b00000000;
  Memory4[0000000000000000000000001000] = 8'b00000010;
  //11, the last term we need to compute(for checking whether the last term)
  Memory1[0000000000000000000000001100] = 8'b00000000; 
  Memory2[0000000000000000000000001100] = 8'b00000000;
  Memory3[0000000000000000000000001100] = 8'b00000000;
  Memory4[0000000000000000000000001100] = 8'b00001011;
  //Needed Registers here
  //t0, initialized to zero for now
  Memory1[0000000000000000000000010000] = 8'b00000000; 
  Memory2[0000000000000000000000010000] = 8'b00000000;
  Memory3[0000000000000000000000010000] = 8'b00000000;
  Memory4[0000000000000000000000010000] = 8'b00000000;
  //t1, initialized to zero for now
  Memory1[0000000000000000000000010100] = 8'b00000000; 
  Memory2[0000000000000000000000010100] = 8'b00000000;
  Memory3[0000000000000000000000010100] = 8'b00000000;
  Memory4[0000000000000000000000010100] = 8'b00000000;
  //t2, initialized to zero for now
  Memory1[0000000000000000000000011000] = 8'b00000000; 
  Memory2[0000000000000000000000011000] = 8'b00000000;
  Memory3[0000000000000000000000011000] = 8'b00000000;
  Memory4[0000000000000000000000011000] = 8'b00000000;
  //t3, initialized to zero for now
  Memory1[0000000000000000000000100000] = 8'b00000000; 
  Memory2[0000000000000000000000100000] = 8'b00000000;
  Memory3[0000000000000000000000100000] = 8'b00000000;
  Memory4[0000000000000000000000100000] = 8'b00000000;
  //t4, initialized to zero for now
  Memory1[0000000000000000000000100100] = 8'b00000000; 
  Memory2[0000000000000000000000100100] = 8'b00000000;
  Memory3[0000000000000000000000100100] = 8'b00000000;
  Memory4[0000000000000000000000100100] = 8'b00000000;

//--------------------PROGRAM LINES START HERE---------------------------

  //Hard coded instruction lines into the memory
  //MAR = 0000 0001, AC=MBR=1    Load info from MAR into MBR then to AC
  Memory1[0000000000000000000000101000] = 8'b01100000;
  Memory2[0000000000000000000000101000] = 8'b00000000;
  Memory3[0000000000000000000000101000] = 8'b00000000;
  Memory4[0000000000000000000000101000] = 8'b00000100;
  //MAR = address of t0, MBR=AC=1, t0 = 1 Put f1 term into t0
  Memory1[0000000000000000000000101100] = 8'b01110000;
  Memory2[0000000000000000000000101100] = 8'b00000000;
  Memory3[0000000000000000000000101100] = 8'b00000000;
  Memory4[0000000000000000000000101100] = 8'b00010000;
  //MAR = address of t1, MBR=AC=1, t1 = 1 Put f2 term into t1
  Memory1[0000000000000000000000110000] = 8'b01110000;
  Memory2[0000000000000000000000110000] = 8'b00000000;
  Memory3[0000000000000000000000110000] = 8'b00000000;
  Memory4[0000000000000000000000110000] = 8'b00010100;
  //Clear AC
  Memory1[0000000000000000000000110100] = 8'b10000000;
  Memory2[0000000000000000000000110100] = 8'b00000000;
  Memory3[0000000000000000000000110100] = 8'b00000000;
  Memory4[0000000000000000000000110100] = 8'b00000000;
  //AC = 0, MAR = address of t2, MBR = AC = 0, t2 = 0 (This is the fibonacci term)
  Memory1[0000000000000000000000111000] = 8'b01110000;
  Memory2[0000000000000000000000111000] = 8'b00000000;
  Memory3[0000000000000000000000111000] = 8'b00000000;
  Memory4[0000000000000000000000111000] = 8'b00011000;
  //MAR = address of 2 the number, AC=MBR=2, load 2 to AC
  Memory1[0000000000000000000000111100] = 8'b01100000;
  Memory2[0000000000000000000000111100] = 8'b00000000;
  Memory3[0000000000000000000000111100] = 8'b00000000;
  Memory4[0000000000000000000000111100] = 8'b00001000;
  //MAR = address of t3, MBR=AC=2, t3 = 2, (store 2 into t3, for start index of loop)
  Memory1[0000000000000000000001000000] = 8'b01110000;
  Memory2[0000000000000000000001000000] = 8'b00000000;
  Memory3[0000000000000000000001000000] = 8'b00000000;
  Memory4[0000000000000000000001000000] = 8'b00011100;
  //MAR = address of 11 the number, AC=MBR=11
  Memory1[0000000000000000000001000100] = 8'b01100000;
  Memory2[0000000000000000000001000100] = 8'b00000000;
  Memory3[0000000000000000000001000100] = 8'b00000000;
  Memory4[0000000000000000000001000100] = 8'b00001100;
  //MAR = address of t4, MBR = AC = t4 = 11 (store 2 into t3, for end index of loop)
  Memory1[0000000000000000000001001000] = 8'b01110000;
  Memory2[0000000000000000000001001000] = 8'b00000000;
  Memory3[0000000000000000000001001000] = 8'b00000000;
  Memory4[0000000000000000000001001000] = 8'b00100000;
  //--------------Loop starts here----------------------------
  //MAR = address of t0, AC=MBR=t0=1 (since f1 = f(n-2) = 1)
  Memory1[0000000000000000000001001100] = 8'b01100000;
  Memory2[0000000000000000000001001100] = 8'b00000000;
  Memory3[0000000000000000000001001100] = 8'b00000000;
  Memory4[0000000000000000000001001100] = 8'b00010000;
  //MAR = address of t1, MBR=t1, AC = AC+MBR = t0+t1 = 2 (computes f3 term)
  Memory1[0000000000000000000001010000] = 8'b00000000;
  Memory2[0000000000000000000001010000] = 8'b00000000;
  Memory3[0000000000000000000001010000] = 8'b00000000;
  Memory4[0000000000000000000001010000] = 8'b00010100;
  //Store the value into t2, which holds our computed fibonacci number
  Memory1[0000000000000000000001010100] = 8'b01110000;
  Memory2[0000000000000000000001010100] = 8'b00000000;
  Memory3[0000000000000000000001010100] = 8'b00000000;
  Memory4[0000000000000000000001010100] = 8'b00011000;
  //MAR = address of t1, AC=MBR=t1
  Memory1[0000000000000000000001011000] = 8'b01100000;
  Memory2[0000000000000000000001011000] = 8'b00000000;
  Memory3[0000000000000000000001011000] = 8'b00000000;
  Memory4[0000000000000000000001011000] = 8'b00010100;
  //MAR = address of t0, t0 = AC = MBR = t1
  //(move content in t1 into t0, f(n-1) became the f(n-2) for the next calculation)
  Memory1[0000000000000000000001011100] = 8'b01110000;
  Memory2[0000000000000000000001011100] = 8'b00000000;
  Memory3[0000000000000000000001011100] = 8'b00000000;
  Memory4[0000000000000000000001011100] = 8'b00010000;
  //MAR = address of t2, AC=MBR=t2
  Memory1[0000000000000000000001100000] = 8'b01100000;
  Memory2[0000000000000000000001100000] = 8'b00000000;
  Memory3[0000000000000000000001100000] = 8'b00000000;
  Memory4[0000000000000000000001100000] = 8'b00011000;
   //MAR = address of t1, t1 = AC = MBR = t2
  //(move content in t2 into t1, current fibonacci number became the f(n-1) for the next calculation)
  Memory1[0000000000000000000001100100] = 8'b01110000;
  Memory2[0000000000000000000001100100] = 8'b00000000;
  Memory3[0000000000000000000001100100] = 8'b00000000;
  Memory4[0000000000000000000001100100] = 8'b00010100;
  //MAR = address of t3, AC=MBR=t3
  Memory1[0000000000000000000001101000] = 8'b01100000;
  Memory2[0000000000000000000001101000] = 8'b00000000;
  Memory3[0000000000000000000001101000] = 8'b00000000;
  Memory4[0000000000000000000001101000] = 8'b00011100;
  //MAR = address of 1(the number), MBR=1, AC = AC+1 = t3+1(calculate incrementation)  
  Memory1[0000000000000000000001101100] = 8'b00000000;
  Memory2[0000000000000000000001101100] = 8'b00000000;
  Memory3[0000000000000000000001101100] = 8'b00000000;
  Memory4[0000000000000000000001101100] = 8'b00000100;
  //MAR = address of t3, MBR = AC = t3 = t3+1 (update the index with incremented index)
  Memory1[0000000000000000000001110000] = 8'b01110000;
  Memory2[0000000000000000000001110000] = 8'b00000000;
  Memory3[0000000000000000000001110000] = 8'b00000000;
  Memory4[0000000000000000000001110000] = 8'b00011100;
  //MAR = address of t3, AC=MBR=t3
  Memory1[0000000000000000000001110100] = 8'b01100000;
  Memory2[0000000000000000000001110100] = 8'b00000000;
  Memory3[0000000000000000000001110100] = 8'b00000000;
  Memory4[0000000000000000000001110100] = 8'b00011100;
  //MAR = address of t4, MBR = t4. AC = AC-MBR = t3-t4 (to check whether t3 = t4)
  Memory1[0000000000000000000001111000] = 8'b00010000;
  Memory2[0000000000000000000001111000] = 8'b00000000;
  Memory3[0000000000000000000001111000] = 8'b00000000;
  Memory4[0000000000000000000001111000] = 8'b00100000;
  //MAR = address of t4, MBR = t4. AC = AC-MBR = t3-t4 (if t3 = t4 = 11, skip to halt)
  //I'm not sure if this line is right
  Memory1[0000000000000000000001111100] = 8'b10010000;
  Memory2[0000000000000000000001111100] = 8'b00000000;
  Memory3[0000000000000000000001111100] = 8'b00000000;
  Memory4[0000000000000000000001111100] = 8'b00001000;
  //Jump to loop tag
  Memory1[0000000000000000000010000000] = 8'b10010000;
  Memory2[0000000000000000000010000000] = 8'b00000000;
  Memory3[0000000000000000000010000000] = 8'b00000000;
  Memory4[0000000000000000000010000000] = 8'b01001100;
  //AC=MBR=t2(f11), use $display to check testbench
  Memory1[0000000000000000000010000100] = 8'b01100000;
  Memory2[0000000000000000000010000100] = 8'b00000000;
  Memory3[0000000000000000000010000100] = 8'b00000000;
  Memory4[0000000000000000000010000100] = 8'b00110000;
  //Stop PC from incrementing, stops program from continue 
  Memory1[0000000000000000000010001000] = 8'b01010000;
  Memory2[0000000000000000000010001000] = 8'b00000000;
  Memory3[0000000000000000000010001000] = 8'b00000000;
  Memory4[0000000000000000000010001000] = 8'b00000000;
*/
  always
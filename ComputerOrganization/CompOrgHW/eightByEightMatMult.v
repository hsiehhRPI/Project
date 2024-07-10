module eightByEightMatMult (mat1, mat2, AC);
	input [31:0] mat1;
	input [31:0] mat2;
	output [31:0] AC;

	reg[31:0] AC;
	reg[63:0] mat1_1 [000:111][000:111];
	reg[63:0] mat2_1 [000:111][000:111];
	integer i, j ,k;

	always@ (A or B) begin
	{mat1_1[000][000], mat1_1[000][001], mat1_1[000][010], mat1_1[000][011], mat1_1[000][100], mat1_1[000][101], mat1_1[000][110], mat1_1[000][111],mat1_1[010][000], mat1_1[010][001], mat1_1[010][010], mat1_1[010][011], mat1_1[010][100], mat1_1[010][101], mat1_1[010][110], mat1_1[010][111], 
	mat1_1[011][000], mat1_1[011][001], mat1_1[011][010], mat1_1[011][011], mat1_1[011][100], mat1_1[011][101], mat1_1[011][110], mat1_1[011][111], 
	mat1_1[100][000], mat1_1[100][001], mat1_1[100][010], mat1_1[100][011], mat1_1[100][100], mat1_1[100][101], mat1_1[100][110], mat1_1[100][111],
	mat1_1[101][000], mat1_1[101][001], mat1_1[101][010], mat1_1[101][011], mat1_1[101][100], mat1_1[101][101], mat1_1[101][110], mat1_1[101][111],
	mat1_1[110][000], mat1_1[110][001], mat1_1[110][010], mat1_1[110][011], mat1_1[110][100], mat1_1[110][101], mat1_1[110][110], mat1_1[110][111], 
	mat1_1[111][000], mat1_1[111][001], mat1_1[111][010], mat1_1[111][011], mat1_1[111][100], mat1_1[111][101], mat1_1[111][110], mat1_1[111][111]
	}






module matmulTB;
	reg [31:0] mat1;
	reg [31:0] mat2;
	wire [31:0] AC;

	Mat_mult (
		.mat1(mat1),
		.mat2(mat2),
		.AC(AC)
	);
	initial begin
	mat1 = 0; mat2 = 0; #100;
	mat1 = {};
	mat2 = {};

Reference:
	https://verilogcodes.blogspot.com/2015/11/verilog-code-for-matrix-multiplication.html 

#include <fstream>
#include <iostream>
#include "Matrix.h"

//DEFAULT CONSTRUCTOR
Matrix::Matrix() {
	//The default size of the matrix is 0x0
	rowC = 0;
	colC = 0;
	fillVal = 0;
	matrix = new double * [rowC];
	for (unsigned int a = 0; a< rowC; a++){
		matrix[a]= new double[colC];
	}
}

//CONSTRUCTOR
//There was a big issue with <optimizing out> for unsign int c
Matrix::Matrix(unsigned int r, unsigned int c, double f) {
		if (r != 0 && c != 0) {
			rowC = r;
			colC = c;
			matrix = new double*[rowC];
			for (unsigned int a = 0; a < rowC; a++){
				matrix[a] = new double[colC];
			}
			for (unsigned int g = 0; g < rowC; g++){
				for (unsigned int h = 0; h < colC; h++) {
					matrix[g][h] = f;
				}
			}
		}
		else{
			Matrix();
		}
	}

//COPY CONSTRUCTOR
Matrix::Matrix(const Matrix& other){
	rowC = other.rowC;
	colC = other.colC;
	matrix = new double *[rowC];
	for (unsigned int a = 0; a< rowC; a++){
		matrix[a]= new double[colC];
	}
	for (unsigned int b = 0; b<rowC; b++) {
		for (unsigned int c = 0; c<colC; c++){
			matrix[b][c] = other.matrix[b][c];
		}	
	}
}

bool Matrix::operator==(const Matrix& other){
		//Comparing current matrix and the matrix that is passed in
		//True is only returned when every position of the two matrix contain identical value
		//To check all values, every position in the is stepped through 
		if (rowC == other.rowC && colC == other.colC) {
			for (unsigned int r = 0; r < rowC; r++){
				for (unsigned int c = 0; c < colC; c++) {
					if (matrix[r][c] != other.matrix[r][c]) {
						return false;
					}
				}
			}
			return true;
		}
		else {
			return false;
		}

	}
bool Matrix::operator!=(const Matrix& other) {
		//This function is the same as above, however, the returned conditions are swapped
		if (rowC == other.rowC && colC == other.colC) {
			for (unsigned int r = 0; r < rowC; r++){
				for (unsigned int c = 0; c < colC; c++) {
					if (matrix[r][c] != other.matrix[r][c]) {
						return true;
					}
				}
			}
			return false;
		}
		else {
			return true;
		}
	}
void Matrix::clear() {
		//Resets the matrix to 0x0
		for (unsigned int a = 0; a < rowC; a++){
			delete [] matrix[a];
		}
		delete[] matrix;
		Matrix();
	}
void Matrix::delMatrix(Matrix& m) {
		for (unsigned int a = 0; a < m.rowC; a++){
			delete [] m.matrix[a];
		}
		delete[] m.matrix;
	}
//Accessor for specific element of the matrix
//Must passed in row number, column number, and a double to contain the value at position
bool Matrix::get(unsigned int r, unsigned int c, double& n) const {
		if (r < rowC && c < colC){
			n = matrix[r][c];
			return true;
		}
		else{
			return false;
		}
	}
//These are some applicable math operation on matrices
void Matrix::multiply_by_coefficient(double coe) {
		//Every value of the matrix will be multiplied by this number
		for (unsigned int r = 0; r < rowC; r++){
			for (unsigned int c = 0; c < colC; c++) {
				matrix[r][c] = coe* matrix[r][c];
			}
		}
	}
bool Matrix::swap_row(unsigned int r1, unsigned int r2) {
		//Checks if the two rows exists in the current matrix
		//Two swap two rows, the content of one of the row is first added to a new pointer array
		//The original value of r1 will is filled by values in user specified r2
		//The new pointer array's value will be inputted into r2 specified by the user
		//This had to use dynamic memory allocation
		if (r1 < rowC && r2 < rowC) {
			double *holder = new double [colC];
			for (unsigned int c = 0; c < colC; c++) {
				holder[c] = matrix[r2][c];
			}
			for (unsigned int k=0; k < colC; k++) {
				matrix[r1][k] = matrix[r2][k];
				matrix[r2][k] = holder[k];
			}
			delete [] holder;
			return true;
		}
		else{
			return false;
		}
	}
void Matrix::transpose() {
		//To be very fair, I am pretty sure this is not the most efficient way of doing it
		//But it is the only way I know how to do it. 
		int nRowDimension = colC;
		int newColDimension = rowC;
		//Creating a new 2D array(Cannot create new matrix object because class type is classified different)
		double** nDimension = new double*[nRowDimension];
		for (int a =0; a< nRowDimension; a++){
			nDimension[a] = new double [newColDimension];
		}
		//Fill in the correct information
		int nDri = 0;
		int nDci = 0;
		for (int y = 0; y < nRowDimension; y++){
			for (int x = 0; x < newColDimension; x++) {
				nDimension[nDri][nDci] = matrix[x][y];
				nDci++;
			}
			nDci*=0;
			nDri++;
		}

		//Will delete later
		//Delete the old matrix
		for (unsigned int n = 0; n < rowC; n++) {
			delete [] matrix[n];
		}
		delete [] matrix;
		rowC = nRowDimension;
		colC = newColDimension;
		matrix = nDimension;
	}
//-------Binary Matrix Operations-------
	//We can only operate when the two matrix have the same dimension
	//The first condition of these functions will be checking the dimension
bool Matrix::add(const Matrix& c) {
		//Elements in the same position of the passed in matrix will be added to current matrix
		//Only the current matrix will be modified
		if (c.rowC == rowC && c.colC == colC){
			for (unsigned int a = 0; a < rowC; a++) {
				for (unsigned int b = 0; b < colC; b++) {
					matrix[a][b] += c.matrix[a][b];
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
bool Matrix::subtract(const Matrix& c) {
		//Elements in the same position of the passed in matrix will be subtraced by current matrix
		//Only the current matrix will be modified
		//Structurally the same as the operation above except is subtraction
		if (c.rowC == rowC && c.colC == colC){
			for (unsigned int a = 0; a < rowC; a++) {
				for (unsigned int b = 0; b < colC; b++) {
					matrix[a][b] -= c.matrix[a][b];
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

//Create a pointer array that contain quadrant arrays
//I really need to take some time to think about this
Matrix* Matrix::quarter() {
		//Okay I really need to think about this
		unsigned int rDim = 0;
		unsigned int cDim = 0;
		//Check if the number of row/column is odd/even
		if (rowC%2==0 && colC%2==0) {
			rDim += rowC/2;
			cDim += colC/2;
		}
		else if (rowC%2 == 0 && colC%2 != 0) {
			rDim += rowC/2;
			cDim += int (colC/2) +1;
		}
		else if (rowC%2 !=0 && colC%2 == 0) {
			rDim += int (rowC/2) +1;
			cDim += colC/2;
		}
		else {
			rDim += int (rowC/2) +1;
			cDim += int (colC/2) +1;
		}

		Matrix* quadMat = new Matrix[4];
		//Making the UL matrix
		//This is correct(2/8 11:35)
		Matrix UL(rDim, cDim, 0);
		for (unsigned int a = 0; a < rDim; a++){
			for (unsigned int b = 0; b < cDim; b++) {
				UL.set(a,b,matrix[a][b]);
			}
		}
		//Stuff gets weird here
		//Making the UR matrix
		Matrix UR(rDim, cDim, 0);
		int urri = 0;
		int urci = 0;
		for (unsigned int a = 0; a < rDim; a++){
			for (unsigned int b = colC-cDim; b < colC; b++) {
				double nVal=matrix[a][b];
				UR.set(urri,urci,nVal);
				urci++;
			}
			urci*=0;
			urri++;
		}
		
		//Making the LL matrix
		Matrix LL(rDim, cDim, 0);
		int llri = 0;
		int llci = 0;
		for (unsigned int a = rowC-rDim; a < rowC; a++){
			for (unsigned int b = 0; b < cDim; b++) {
				double nVal = matrix[a][b];
				LL.set(llri,llci,nVal);
				llci++;
			}
			llci*=0;
			llri++;
		}
		
		//Making the LR matrix
		Matrix LR(rDim, cDim, 0);
		int lrri = 0;
		int lrci = 0;
			for (unsigned int a = rowC-rDim; a < rowC; a++){
				for (unsigned int b = colC-cDim; b < colC; b++) {
					LR.set(lrri,lrci,matrix[a][b]);
					lrci++;
				}
				lrci*=0;
				lrri++;
			}

		for (int a = 0; a < 4; a++) {
			delMatrix(quadMat[a]);
		}
		quadMat[0] = UL;
		quadMat[1] = UR;
		quadMat[2] = LL;
		quadMat[3] = LR;
		return quadMat;
	}
std::ostream& operator<<(std::ostream& out, const Matrix& m){
	//This operator prints out the values needed by the input Matrix object.
	double i;
	out <<"\n"<< m.num_rows() << " x "<< m.num_cols()<<" matrix:"<<std::endl;
	if (m.num_rows()==0) {
		out << "[   ]" << std::endl;
	}
	else{
		for (int u = 0; u < m.num_rows(); u++) {
		for (int v = 0; v < m.num_cols(); v++) {
			if (u==0 && v==0){
				m.get(u,v,i);
				out << "[ " << i;
			}
			else if (v+1 == m.num_cols() && u+1!=m.num_rows()) {
				m.get(u,v,i);
				out <<" "<<i<<std::endl;
			}
			else{
				m.get(u,v,i);
				out <<" "<< i;
			}
		}
	}
	out << " ]" << std::endl;
	}
	
	return out;
}
#include <fstream>
#include <iostream>
#ifndef __Matrix_h_
#define __Matrix_h_
//About this class:
/*This class create matrices by using 2D arrays which serves 
as the rows and columns of the matrix. 
*/
class Matrix{
public:
	//DEFAULT CONSTRUCTOR
	Matrix();

	//CONSTRUCTOR
	//There was a big issue with <optimizing out> for unsign int c
	Matrix(unsigned int r, unsigned int c, double f);

	//COPY CONSTRUCTOR
	Matrix(const Matrix& other);
	//DECONSTUCTOR
	//I tried to make a deconstructor based on the template class example
	//But it does not actually clean the memory leaks
	~Matrix() {
		//for(unsigned int s=0; s<rowC-1; s++){
		//	delete [] matrix[s];
		//}
		//delete [] matrix;
	}

	//-------BASIC FUNCTIONS-------
	//Operator ==
	bool operator==(const Matrix& other);
	//Operator !=
	bool operator!=(const Matrix& other);
	//Accessor for number of rows
	int num_rows() const {return rowC;}
	//Accessor for number of columns
	int num_cols() const {return colC;}

	void clear();
	//Custom helper function to make my life easier when doing quater matrix
	//Deletes matrix object that gets passed in
	void delMatrix(Matrix& m);

	//Accessor for specific element of the matrix
	//Must passed in row number, column number, and a double to contain the value at position
	bool get(unsigned int r, unsigned int c, double& n) const;
	//Modifier, n will replace value at the given position
//Modifier, n will replace value at the given position
	bool set(unsigned int r, unsigned int c, double n) {
		if (r<rowC  && c<colC ){
			matrix[r][c] = n;
			return true;
		}
		else{
			return false;
		}
	}// -------Simple Matrix Operations-------
	//These are some applicable math operation on matrices
	void multiply_by_coefficient(double coe);
	bool swap_row(unsigned int r1, unsigned int r2);
	//This operation is already prewritten in matrix_main.cpp
	void rref();
	//This one is probably the hardest to write in my opinion
	void transpose();
	//-------Binary Matrix Operations-------
	//We can only operate when the two matrix have the same dimension
	//The first condition of these functions will be checking the dimension
	bool add(const Matrix& c);
	bool subtract(const Matrix& c);
	//-------Harder Matrix Operations-------
	//-------Harder Matrix Operations-------
double* get_row(unsigned int i){
		//Contrary to getting one specific position of the matrix, 
		//This function returns an array containing all values in specified row
		if (i > rowC) {
			return NULL;
		}
		else {
			double* saidCol = new double [colC];
			for (unsigned int c = 0; c < colC; c++) {
				saidCol[c] = matrix[i][c];
			}
			return saidCol;
		}
	}
double* get_col(unsigned int i){
		//This function returns a pointer array containing all the values in the same column
		if (i > colC) {
			return NULL;
		}
		else {
			double* saidCol= new double [colC];
			for (unsigned int r = 0; r < rowC; r++) {
				saidCol[r] = matrix[r][i];
			}
			return saidCol;
		}
	}
	Matrix* quarter();


private:
	double** matrix;		//This is the actual 2D array
	double fillVal;
	unsigned int rowC;
	unsigned int colC;
	
};

//-------Overloaded Output Operator--------
std::ostream& operator<<(std::ostream& out, const Matrix& m);
#endif
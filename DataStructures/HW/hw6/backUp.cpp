#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

void findFill(int r, int c, int rows, int cols, std::string word, std::vector<int> positions, int count,std::vector<std::vector<int>> &POSFILL) {
	if (count == 8) {
		return;
	}
	if (count == 0 ) {
		//Search E
		while (r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 1) {
		//Search W
		while (r > -1 && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 2) {
		//Search S
		while (c < cols && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 3) {
		//Search N
		while (c > -1 && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			c--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 4) {
		//Search NE
		while (c > -1 &&  r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r--;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 5) {
		//Search NW
		while (c > -1 &&  r > -1 && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}

	}
	if (count == 6) {
		//Search SE
		while (c < cols &&  r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
	if (count == 7) {
		//Search SW
		while (c < cols &&  r > -1 && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
		else {
			POSFILL.push_back(positions);
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL);
		}
	}
}


/*
Some fundamental issue to address:
	- Find a starting position to fill the word in: Can be a blank space '.', the start of the word, or end of the word
	- Make sure there is enough space to fill the word in
	Honestly the top two problem is already pretty hard to address, so the following problem is a lower priority
	- The forbidden word should not appear
*/
/*
bool checkLinear(int x1, int y1, int x2, int y2) {
	//Check if the points are in a straight line(vertical or horizontal)
	if (x1 == x2 && y1 != y2) {
		return true;
	} 
	else if (y1 == y2 && x1 != x2) {
		return true;
	}
	//Check if the points are in a diagonal line
	else if (x2-x1 == y2-y1) {
		return true;
	}
	else {
		return false;
	}
}


//The following function attempts to fill the word in using recursion
void fill (char ** & grid, int rows, int cols, int r, int c, std::string essential, std::vector<int> &positions, int index) {
	std::cout << positions.size()<<std::endl;
	std::cout << "(" << r << "," << c << ")" <<std::endl;
	std::cout << index << std::endl;
	//Fill in the word recursively
	if (index == essential.size()) {
		int letter = 0;
		for (int n = 0; n+1 < positions.size()+1; n++) {
			grid[positions[n]][positions[n+1]] = essential[letter];
			letter++;
			n++;
		}
		positions.clear();
		return;
	}
	if ((grid[r][c] == '.' && rows >= essential.size()) || (grid[r][c] == essential[index] && rows >= essential.size())) {
		if (positions.size() == 0) {
			positions.push_back(r);
			positions.push_back(c);
			fill(grid, rows, cols, r+1, c, essential, positions, index+1);
		}
		else {
			if (checkLinear(positions[0], positions[1], r, c) == true) {
				positions.push_back(r);
				positions.push_back(c);
				fill(grid, rows, cols, r+1, c, essential, positions, index+1);
			}
		}
	}
	if ((grid[r][c] == '.' && cols >= essential.size())||(grid[r][c] == essential[index] && cols >= essential.size())) {
		if (positions.size() == 0) {
			positions.push_back(r);
			positions.push_back(c);
			fill(grid, rows, cols, r, c+1, essential, positions, index+1);
		}
		else {
			if (checkLinear(positions[0], positions[1], r, c) == true) {
				positions.push_back(r);
				positions.push_back(c);
				fill(grid, rows, cols, r, c+1, essential, positions, index+1);
			}
		}
	}
	if ((grid[r][c] == '.' && cols >= essential.size() && rows >= essential.size())||(grid[r][c] == essential[index] && cols >= essential.size() && rows >= essential.size())) {
		if (positions.size() == 0) {
			positions.push_back(r);
			positions.push_back(c);
			grid[r][c] == essential[index];

			fill(grid, rows, cols, r+1, c+1, essential, positions, index+1);
		}
		else {
			if (checkLinear(positions[0], positions[1], r, c) == true) {
				positions.push_back(r);
				positions.push_back(c);
				fill(grid, rows, cols, r+1, c+1, essential, positions, index+1);
			}
		}
	}
}

void findNextStart(int nextX, int nextY, bool rev, char ** & grid, int rows, int cols, std::string essential) {
	//The first two argument are the returned value of the starting x and y value
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (grid[r][c] == '.') {
				nextX = r;
				nextY = c;
				return;
			}
			else if (grid[r][c] == essential[0]) {
				nextX = r;
				nextY = c;
				return;
			}
			else if (grid[r][c] == essential[essential.size()-1]) {
				nextX = r;
				nextY = c;
				rev = true;
				return;
			}
		}	
	} 
}*/


//Stoping condition for my recursion
bool sameGrid (char ** & grid1, char** & grid2, int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (grid1[r][c] != grid2[r][c]) {
				return false;
			}
		}
	}
	return true;
}

void fillHorizon(char**grid, int rows, int cols, int r, int c, std::string word) {
	//Fill the word in horizontally
	for (int n = 0; n < word.size(); n++) {
		grid[r][c] =  word[n];
		c++;
	}
}

void filldiag(char**grid, int rows, int cols, int r, int c, std::string word) {
	//Fill the word in diagonally
	for (int n = 0; n < word.size(); n++) {
		grid[r][c] =  word[n];
		c++;
		r++;
	}
}

void fillVert(char**grid, int rows, int cols, int r, int c, std::string word) {
	//Fill the word in vertically
	for (int n = 0; n < word.size(); n++) {
		grid[r][c] =  word[n];
		r++;
	}
}

std::string wordRev(std::string word) {
	std::string revWord;
	for (int n = word.size()-1; n > -1; n--) {
		revWord.push_back(word[n]);
	}
	return revWord;
}

bool gridCheck(char**grid, int rows, int cols, std::vector<std::string> essential, std::vector<std::string> forbidden) {
	//We are gonna check if there are forbidden words in the grid first, if there is a forbidden word in the grid, we are going to return false
	int invCount = 0;
	int vCount = 0;
	int windex = 0;
	int xHold;
	int yHold;
	std::string target;
	int directions = 8;
	std::vector<std::string> wordHold;
	for (int n = 0; n < forbidden.size(); n ++) {
		for (int x = 0; x<rows; x++){
			for (int y = 0; y < cols; y++) {
				if (grid[x][y] == forbidden[n][windex]) {
					xHold = x;
					yHold = y;
					target.push_back(forbidden[n][windex]);
					windex++;
					if (rows-xHold < forbidden[n].size()) {

					}
					else if (xHold < forbidden[n].size()) {

					}
					else if (cols-yHold < forbidden[n].size()) {

					}
					else if (yHold < forbidden[n].size()) {

					}
				}
			}
		}
	}
}




void nextPoint(char**grid, int rows, int cols, int r, int c, std::string word) {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			if (grid[x][y] == '.') {
				x = r;
				y = c;
				return;
			}
			else if (grid[x][y] == word[0]&&rows-r >= word.size() || grid[x][y] == word[0]&&cols-c >= word.size()) {
				//Check if the word can be filled given the first character
				x = r;
				y = c;
				return;
			}
			else if (grid[x][y] == word[word.size()-1]&&rows-r >= word.size() || grid[x][y] == word[word.size()-1]&&cols-c >= word.size()) {
				//Check if the word can be filled in reverse
				x = r;
				y = c;
				return;
			}
		}
	}
}

std::vector<char**> getAllPath(std::vector<std::string> essential, std::vector<std::string> forbidden, int rows, int cols, int nFilled) {
	if (nFilled == essential.size() && gridCheck == true) {

		return validGrids; 
	}
	if (nFilled != essential.size()) {
		if (essential[nFilled].size() <= rows) {
			fillHorizon(grid, rows, cols, r, c, essential[nFilled]);
			nFilled++;

			getAllPath(essential, forbidden, rows, cols, nFilled);
		}
		if (essential[nFilled].size() <= cols) {
			fillVert(grid, rows, cols, r, c, essential[nFilled]);
			nFilled++;

			getAllPath(essential, forbidden, rows, cols, nFilled);
		}
		if (essential[nFilled].size() <= rows && essential[nFilled].size() <= cols) {
			filldiag(grid, rows, cols, r, c, essential[nFilled]);
			nFilled++;

			getAllPath(essential, forbidden, rows, cols, nFilled);
		}
	}
	return validGrids;
}


//Sorting algorithm: Sort the words by length, if the words are same length, sort by lexicographical order
bool sortByMaxLen(const std::string& w1, const std::string& w2) {
	if (w1.size() > w2.size()) {
		return true;
	}
	else if (w1.size()< w2.size()) {
		return false;
	}
	else {
		if (w1 < w2) {
			return true;
		}
		else if (w1 > w2) {
			return false;
		}
		else {
			return true;
		}
	}
}


int main(int argc, char* argv[]) {
	//Assign the metrics from the command line to variables for later use
	std::string puzzle = argv[1];
	std::string nSol = argv[2];


	std::ifstream inFile(puzzle);
	if (!inFile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	std::string reqs;
	std::vector<std::string> allInfo;
	while (inFile>>reqs) {allInfo.push_back(reqs);}


	//Separate the informations into two other vector
	//One would contain words that should appear, another for words that shouldn't
	std::vector<std::string> essential;
	std::vector<std::string> forbidden;
	for (int o = 0; o < allInfo.size(); o++){
		if(allInfo[o-1].find("+") != std::string::npos) {
			essential.push_back(allInfo[o]);
		}
		else if (allInfo[o-1].find("-") != std::string::npos) {
			allInfo[o].erase(allInfo[o].begin());
			forbidden.push_back(allInfo[o]);
		}
	}


	//Making the 2D array with dimension given by the input file
	int rows = stoi (allInfo[0]);
	int cols = stoi(allInfo[1]);
	char ** grid = new char * [rows];
	for (int n = 0; n < rows; n++) {
		grid[n] = new char [cols];
	}
	//Fill the grid with "." so later we could check whether the grid is done
	for (int t = 0; t < rows; t++) {
		for (int r = 0; r < cols; r++) {
			grid[t][r] = '.';
		}
	}
	//Test printing
	std::cout << "Rows" <<rows << std::endl;
	std::cout << "Cols" <<cols << std::endl;
	for (int v = 0; v < rows; v++) {
		for (int f = 0; f < cols; f++) {
			std::cout << grid[v][f];
		}
		std::cout << std::endl;
	}
	//To ensure the big words are definitely there:
	//The list of essential words are sorted by length first
	sort(essential.begin(), essential.end(), sortByMaxLen);
	int index = 0;
	std::vector<int> positions;
	fill(grid, rows, cols, 0, 0, essential[0], positions,index);
	

	std::cout << "position size:" << positions.size() << std::endl;
	for (int v = 0; v < rows; v++) {
		for (int f = 0; f < cols; f++) {
			std::cout << grid[v][f];
		}
		std::cout << std::endl;
	}
	std::cout << essential[0] << std::endl;
	fill(grid, rows, cols, 0, 1, essential[1], positions,index);
	std::cout << "position size:" << positions.size() << std::endl;
	for (int v = 0; v < rows; v++) {
		for (int f = 0; f < cols; f++) {
			std::cout << grid[v][f];
		}
		std::cout << std::endl;
	}

	std::vector<char**> validGrids;

}
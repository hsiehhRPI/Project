#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

//-----------GLOBAL VAR--------------
//-----------------------------------

/*
Some fundamental issue to address:
	- Find a starting position to fill the word in: Can be a blank space '.', the start of the word, or end of the word
	- Make sure there is enough space to fill the word in
	Honestly the top two problem is already pretty hard to address, so the following problem is a lower priority
	- The forbidden word should not appear
*/

//Thought process:
//Find and fill in all position the given word can fit
//Match the grids of each word together into a board(the once that are valid, forbidden words are not accounted)
//Find the grids with forbidden words in them, eliminate them.
//Clean it up and output the result to a file

char** makeGrid (int rows, int cols) {
	//Making the 2D array with dimension given by the input file
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
	return grid;
}

//Since there are a lot of 2D arrays used in this function,
//to prevent memory leak, the destroy function below is implimented
//to free up memories 
void destroyGrid(char** grid, int rows) {
	for (int r = 0; r < rows; r++) {
		delete [] grid[r];
	}
	delete [] grid;
	return;
}

//Finding how many ways a word can be filled in a board
//Process: Find the 8 direction arount the point
//If the path is not long enough to fill in the word, the path is discarded
//If the path exist, fill the word in and append it to a vector that hold the grids
void findFill(int r, int c, int rows, int cols, std::string word,std::vector<int> positions, int count, std::vector<char**> &POSFILL, int windex) {
	if (count == 8) {
		return;
	}
	if (count == 0 ) {
		//Search S
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 1) {
		//Search N
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 2) {
		//Search E
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 3) {
		//Search W
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			c--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 4) {
		//Search SW
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
			c--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 5) {
		//Search NW
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r--;
			c--;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 6) {
		//Search SE
		while (r >= 0 && c>= 0 && c < cols && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r++;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
	if (count == 7) {
		//Search NE
		while (r >= 0 && c>= 0 && r < rows && positions.size()/2 <= word.size()) {
			positions.push_back(r);
			positions.push_back(c);
			r--;
			c++;
		}
		if (positions.size()/2 != word.size()) {
			positions.clear();
			r*=0;
			c*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
		else {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			int n = 0;
			while (n<positions.size()-1 && windex < word.size()) {
				newGrid[positions[n]][positions[n+1]] = word[windex];
				revFill[positions[n]][positions[n+1]] = word[word.size()-1-windex];
				n++;
				n++;
				windex++;
			}
			POSFILL.push_back(newGrid);
			POSFILL.push_back(revFill);
			destroyGrid(revFill, rows);
			destroyGrid(newGrid, rows);
			positions.clear();
			r*=0;
			c*=0;
			windex*=0;
			findFill(r,c,rows,cols,word,positions,count+1,POSFILL, windex);
		}
	}
}


//Just like the name suggested, this function checks if the two grids are the same(we want to include only unique )
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

//This function makes a copy of g1, and if the condition is met, will impose g2 onto g1.
void combineGrid (char**& g1, char**& g2, int rows, int cols, std::vector<char**> combGrid) {
	char** combined = makeGrid(rows, cols);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (g1[r][c] != '.' && g2[r][c] != '.' && g1[r][c] != g2[r][c]) {
				destroyGrid(combined,rows);
				return;
			}
			else if (g1[r][c] == '.' && g2[r][c] != '.') {
				combined[r][c] = g2[r][c];
			}
			else if (g1[r][c] != '.' && g2[r][c] == '.') {
				combined[r][c] = g1[r][c];
			}
			else if (g1[r][c] == g2[r][c]) {
				combined[r][c] = g1[r][c];
			}
		}
	}
	combGrid.push_back(combined);
	destroyGrid(combined,rows);
	return;
}

//This function checks if the two grids can combine together
bool combinable (char**& g1, char**& g2, int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (g1[r][c] != '.' && g2[r][c] != '.' && g1[r][c] != g2[r][c]) {
				return false;
			}
		}
	}
	return true;
}


//In all honesty, this one I am quite clueless as to how to tackle this problem
//I struggle to write a recursion for this question
//I tried my best to do it but it doesn't seem very effective
/*
void findAllGrid (std::vector<char**>& holder, char** g1, std::vector<std::vector<std::vector<char**>>>& incomplete, std::vector<char**>& intermediate, int rows, int cols, int w, int p, int f, int count) {
	if (count == incomplete.size()) {
		holder.push_back(intermediate[intermediate.size()-1]);
		intermediate.clear();
		return;
	}
	if (f == 0 && count < incomplete.size()) {
		combineGrid(g1, incomplete[w][p][f], rows, cols, intermediate);
		findAllGrid(holder, g1, incomplete, intermediate, rows, cols, w, p, f+1, count+1);
	}
	if (f == 1 && count < incomplete.size()) {
		combineGrid(intermediate[intermediate.size()-1], incomplete[w][p][f], rows, cols, intermediate);
		findAllGrid(holder, g1, incomplete, intermediate, rows, cols, w, p+1, f*0, count+1);
	}
	if (p == incomplete[0][0].size()-1 && count < incomplete.size()) {
		combineGrid(intermediate[intermediate.size()-1], incomplete[w][p][f], rows, cols, intermediate);
		findAllGrid(holder, g1, incomplete, intermediate, rows, cols, w+1, p*0, f*0, count+1);
	}
}

//This function utilize findFill(to find the possible positions of the forbidden word) and combinable(to see if the word could be overlayed, if so, it is invalid)
bool checkForbidden(std::vector<std::string> forbidden, std::vector<char**> posGrid, std::vector<char**> correct, int rows, int cols){
	std::vector<std::vector<std::vector<char**>>> forbiddenFill;
	std::vector<std::vector<char**>> vFill;

	for (int n = 0; n < forbidden.size(); n++) {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				findFill(0,0,rows,cols,forbidden[n],positions,0,POSFILL, 0);
				vFill.push_back(POSFILL);
				POSFILL.clear();
			}
		}
		forbiddenFill.push_back(vFill);
	}
	for (int t = 0 ; t < posGrid.size(); t++) {
		for (int z = 0; z < forbiddenFill.size(); z++) {
			for (int g = 0; g < forbiddenFill[z].size(); g++) {
				for (int b = 0; b < forbiddenFill[z][g].size(); b++) {
					bool result = combinable(posGrid[t],forbiddenFill[z][g][b], rows cols);

				}
			}
		}
		if (result == false) {
			correct.push_back(posGrid[t]);				
		}
	}
}
*/

//Helper function, it helps me to see how each functions are executing by printing the grid to the consol
void print (char** gr, int rows, int cols) {
	for (int c = 0; c < cols; c++) {
		for (int r = 0; r < rows; r++) {
			std::cout << gr[r][c];
		}
		std::cout<<std::endl;
	}
	return;
}
/*
std::string printGrid (char** gr, int rows, int cols, std::string alphabet) {
	std::string format;
	for (int c = 0; c < cols; c++) {
		for (int r = 0; r < rows; r++) {
			std::string::iterator itr = alphabet.find((std::string)gr[c][r]);
			format.push_back(str(*itr));
		}
		format.push_back('\n');
	}
	return format;
}
*/

int main(int argc, char* argv[]) {
	//Assign the metrics from the command line to variables for later use
	std::string puzzle = argv[1];
	std::string outFile = argv[2];
	std::string nSol = argv[3];


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
	for (int o = 1; o < allInfo.size(); o++){
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
	if (rows==0 || cols==0) {
		exit(1);
	}
	//We technically only need to find how one words is filled
	//The board of the first word filled will be our base board
	std::vector<std::vector<char**>> validPos;
	std::vector<char**> POSFILL;
	int count = 0;
	std::vector<int> positions;
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			findFill(x,y,rows,cols,essential[0],positions,count,POSFILL, 0);
			if (POSFILL.size()!=0) {
				validPos.push_back(POSFILL);
				POSFILL.clear();
			}
		}
	}
	std::vector <char**> finished;
	int w =0;




	for (int n = 0; n < validPos.size(); n++) {
		for (int v = 0; v < validPos[n].size(); v++) {
			char** newGrid = makeGrid(rows, cols);
			char** revFill = makeGrid(rows, cols);
			for (int e = 0; e < rows; e++) {
				for (int a = 0; a < cols; a++) {
					for (int m = 0; m < essential[0].size(); m++) {
						if (validPos[n][v][e][a] == essential[0][m]) {
							newGrid[e][a] = essential[0][m];
							revFill[e][a] = essential[0][m];
						}
					}
				}
			}
			for (int x = 0; x < rows; x++) {
				for (int y = 0; y < cols; y++) {
					for (int h = 1; h < essential.size(); h++) {
						if (validPos[n][v][x][y] == '.') {
							newGrid[x][y] = essential[h][w];
							revFill[x][y] = essential[h][essential[h].size()-1-w];
							w++;
						}
					}
				}
			}
			finished.push_back(newGrid);
			finished.push_back(revFill);
			destroyGrid(newGrid,rows);
			destroyGrid(revFill,rows);
			w*=0;
		}
	}	

	//My printing function is faulty as of currently, so this is a projected output code:
	//It prints fine in the consol but not to a file(memory leak)
	//Where compGrid is a vector of properly checked grids 
	/*
	if (nSol == "one_solution") {
		std::ofstream outfile (outFile);
		outfile << 1 <<" solution(s)"<<std::endl;
		outfile << printGrid(finished[0], rows, cols) << std::endl;
		outfile.close();
	}
	else if (nSol == "all_solutions") {
		std::string sol = std::to_string((int)finished.size());
		std::ofstream outfile (outFile);
		outfile << sol <<" solution(s)"<<std::endl;
		for (int n = 0; n < finished.size(); n++) {
			printGrid(outfile,finished[n], rows, cols) << std::endl;
		}
		outfile.close();
	}
	*/

}
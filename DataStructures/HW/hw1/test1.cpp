#include <iostream>
#include <fstream>
#include <vector>

//left flushed function
/*
std::string lFlush(int charLim, std::vector<std::string> info, std::vector<int> wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;		//This variable is the index of the word
	int counter = 0;	//This variable keeps track the character limit
	std::vector<std::string> lFormats;		//Stores formatted lines
	int lSpace;
	std::string newLine;
	while (iter < info.size()) {
		while (counter <= charLim) {
			if (counter += wordLen[iter] < charLim-1) {
				std::cout << info[iter].size()<< "|" << std::endl;
				counter += 1;
				counter += wordLen[iter];
				newLine.append(info[iter]);
				newLine.append(" ");
				iter++;
				std::cout << counter << "|" << newLine.size() << "|" << newLine << std::endl;
			} else if (counter +wordLen[iter]< charLim) {
				counter += wordLen[iter];
				newLine.append(info[iter]);
				iter++;
			} 
		}
		if (newLine.size() < charLim){
			lSpace = charLim - newLine.size();
			for (int k = 0; k<lSpace; k++) {
				newLine.append(" ");
			}
		}
		lFormats.push_back(newLine);
		newLine.clear();
		lSpace*=0;
		counter*=0;
	}
	for (int i =0; i<lFormats.size();i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
}
*/
std::string lFlush(int charLim, std::vector<std::string> info, std::vector<int> wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;
	int counter = 0;
	int lSpace;
	std::string newLine;
	std::vector<std::string> lFormats;
	while (iter < info.size()) {
		counter += wordLen[iter];
		if (iter == info.size()-1 && newLine.size() < charLim){
			newLine.append(info[iter]);
			lSpace = charLim - counter;
			for (int n =0; n < lSpace; n++) {
				newLine.append(" ");
			}
			lFormats.push_back(newLine);
			counter *= 0;
			iter ++;
		} else if (counter <= charLim-1) {
			newLine.append(info[iter]);
			newLine.append(" ");
			counter ++;
			iter ++;
		} else if (counter == charLim+1) {
			newLine.append(info[iter]); 
			iter ++;
		}
		else if (newLine.size()> charLim/*iter != info.size()-1*/) {
				newLine.erase(newLine.size()-wordLen[iter], wordLen[iter]);
				iter --;
				counter -= wordLen[iter];
		} 
		else {
			lSpace = counter - counter;
			while(newLine.size()!=charLim) {
				newLine.append(" ");
			}
			if (newLine.size() == charLim){
				lFormats.push_back(newLine);
				newLine.clear();
				counter*=0;
			}
		}
	}
	for (int i = 0; i < lFormats.size(); i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout<<"\n";
}


//left flushed function
/*
std::string lFlush(int charLim, std::vector<std::string> info, std::vector<int> wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;		//This variable is the index of the word
	int counter = 0;	//This variable keeps track the character limit
	counter += wordLen[iter];
	std::vector<std::string> lFormats;		//Stores formatted lines
	int lSpace;
	std::string newLine;
	while (iter < info.size()) {
		while (counter <= charLim) {
			if (counter += wordLen[iter] < charLim-1) {
				counter += 1;
				counter += wordLen[iter];
				newLine.append(info[iter]);
				newLine.append(" ");
				iter++;
			} else if (counter +wordLen[iter]< charLim) {
				counter += wordLen[iter];
				newLine.append(info[iter]);
				iter++;
			} 
		}
		if (newLine.size() < charLim){
			lSpace = charLim - newLine.size();
			for (int k = 0; k<lSpace; k++) {
				newLine.append(" ");
			}
		}
		lFormats.push_back(newLine);
		newLine.clear();
		lSpace*=0;
		counter*=0;
	}
	for (int i =0; i<lFormats.size();i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
}
*/

//right flushed function(What is going on?)
/*std::string rFlush(int charLim, std::vector<std::string> info, std::vector<int> wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;		//This variable is the index of the word
	int counter = 0;	//This variable keeps track the character limit
	counter += wordLen[iter];
	std::vector<std::string> lFormats;		//Stores formatted lines
	std::vector<int> wordsPerLine;			//Keeps count of how many words per line 
	int wCount = 0;
	int lSpace;
	std::string newLine;
	while (iter < info.size()) {
		while (counter <= charLim) {
			if (counter += wordLen[iter] < charLim-1) {
				counter += 1;
				counter += wordLen[iter];
				newLine.append(info[iter]);
				newLine.append(" ");
				iter++;
			} else if (counter +wordLen[iter]< charLim) {
				counter += wordLen[iter];
				newLine.append(info[iter]);
				iter++;
			} 
		}
		if (newLine.size() < charLim){
			lSpace = charLim - newLine.size();
			for (int k = 0; k<lSpace; k++) {
				newLine.insert(0, " ");
			}
		}
		lFormats.push_back(newLine);
		newLine.clear();
		lSpace*=0;
		counter*=0;
	}
	for (int i =0; i<lFormats.size();i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
}*/
std::string justify(int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;					
	int counter = 0;						//Guard for not exceeding max length given by the command line
	int wCount = 0;							//Count how many words are in a line
	int lSpace;								//Keeps track of extra space for each line
	std::vector<std::string> wInLine;		//Holds only the characters of each line first
	std::string newLine;					//Each line that are formatted first
	std::vector<std::string> lFormats;		//Holds each formatted lines
	std::string space;
	while (iter < info.size()) {
		counter += wordLen[iter];
		if (wCount == 0) {
			wInLine.push_back(info[iter]);
			wInLine.push_back(" ");
			counter ++;
			iter ++;
			wCount ++;
		} else if (counter <= charLim-1 && counter != 0) {
			wInLine.push_back(" ");
			wInLine.push_back(info[iter]);
			counter ++;
			wCount ++;
			iter ++;
		} else if (counter == charLim+1){
			wInLine.push_back(info[iter]); 
			wCount ++;
			iter ++;
		} else {
			if (iter != info.size()-1) {
				counter -= wordLen[iter];
				lSpace = (charLim-counter)/(wCount-1);
				newLine.append(wInLine[0]);
				for (int i = 0; i < lSpace; i++) {
					space.append(" ");
				}
				for (int n =2; n < wInLine.size(); n++) {
					newLine.append(space);
					newLine.append(wInLine[n]);
				}
				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				counter *= 0;
				wCount*=0;
			}
			else {
				lSpace = (charLim-counter)/(wCount-1);
				newLine.append(wInLine[0]);
				for (int i = 0; i < lSpace; i++) {
					space.append(" ");
				}
				for (int n =2; n < wInLine.size(); n++) {
					newLine.append(space);
					newLine.append(wInLine[n]);
				}
				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				counter *= 0;
				wCount*=0;

			}
		}
	}
	newLine.append(wInLine[0]);
	for (int u = 1; u < wInLine.size(); u++) {
		newLine.append(" ");
		newLine.append(wInLine[u]);
	}
	lFormats.push_back(newLine);
	for (int i = 0; i < lFormats.size(); i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout<<"\n";
}

// This one is pretty good
/*std::string justify(int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;					
	int counter = 0;						//Guard for not exceeding max length given by the command line
	int wCount = 0;							//Count how many words are in a line
	int lSpace;								//Keeps track of extra space for each line
	std::vector<std::string> wInLine;		//Holds only the characters of each line first
	std::string newLine;					//Each line that are formatted first
	std::vector<std::string> lFormats;		//Holds each formatted lines
	std::string space;
	while (iter < info.size()) {
		counter += wordLen[iter];
		if (wCount == 0) {
			wInLine.push_back(info[iter]);
			wInLine.push_back(" ");
			counter ++;
			iter ++;
			wCount ++;
		} else if (counter <= charLim-1 && counter != 0) {
			wInLine.push_back(" ");
			wInLine.push_back(info[iter]);
			counter ++;
			wCount ++;
			iter ++;
		} else if (counter == charLim+1){
			wInLine.push_back(info[iter]); 
			wCount ++;
			iter ++;
		} else {
			if (iter != info.size()-1) {
				counter -= wordLen[iter];
				lSpace = (charLim-counter)/(wCount-1);
				newLine.append(wInLine[0]);
				for (int i = 0; i < lSpace; i++) {
					space.append(" ");
				}
				for (int n =2; n < wInLine.size(); n++) {
					newLine.append(space);
					newLine.append(wInLine[n]);
				}
				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				counter *= 0;
				wCount*=0;
			}
			else {
				lSpace = (charLim-counter)/(wCount-1);
				newLine.append(wInLine[0]);
				for (int i = 0; i < lSpace; i++) {
					space.append(" ");
				}
				for (int n =2; n < wInLine.size(); n++) {
					newLine.append(space);
					newLine.append(wInLine[n]);
				}
				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				counter *= 0;
				wCount*=0;

			}
		}
	}
	newLine.append(wInLine[0]);
	for (int u = 1; u < wInLine.size(); u++) {
		newLine.append(" ");
		newLine.append(wInLine[u]);
	}
	lFormats.push_back(newLine);
	for (int i = 0; i < lFormats.size(); i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout<<"\n";
}*/
/*
std::string justify(int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	int tLineLen = charLim + 4; //Total length of each line
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout << "\n";
	int iter = 0;					
	int counter = 0;						//Guard for not exceeding max length given by the command line
	int wCount = 0;							//Count how many words are in a line
	int lSpace;								//Keeps track of extra space for each line
	int uneven;								//Accounts for extra spaces
	int indexHold = 1;							//How words already have extra space
	std::vector<std::string> wInLine;		//Holds only the characters of each line first
	std::string newLine;					//Each line that are formatted first
	std::vector<std::string> lFormats;		//Holds each formatted lines
	std::string space;
	while (iter < info.size()) {
		counter += wordLen[iter];
		if (wCount == 0) {
			wInLine.push_back(info[iter]);
			wInLine.push_back(" ");
			counter ++;
			iter ++;
			wCount ++;
		} else if (counter <= charLim-1 && counter != 0) {
			wInLine.push_back(info[iter]);
			wInLine.push_back(" ");
			counter ++;
			wCount ++;
			iter ++;
		} else if (counter == charLim+1){
			wInLine.push_back(info[iter]); 
			wCount ++;
			iter ++;
		} else {
			std::cout << wInLine.size() << "|";					//Okay so it was something from now on that is acting weird
			if (counter > charLim){
					counter-=wordLen[iter];
			}
			uneven = charLim-counter;
			if (uneven == 0) {
				lSpace = (charLim-counter) / (wCount-1);
				for (int i = 0; i < lSpace; i++) {
					space.append(" ");
				}
				newLine.append(wInLine[0]);
				for (int u = 1; u < wInLine.size(); u++) {
					newLine.append(space);
					newLine.append(wInLine[u]);
				}
				std::cout<<newLine<<std::endl;
				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				uneven*=0;
				counter*=0;
				wCount*=0;
				lSpace*=0;
			}
			else{
				lSpace = (charLim-counter-uneven) / (wCount-1);
				for (int n = 0; n < lSpace; n++) {
					space.append(" ");
				}
				newLine.append(wInLine[0]);
				for (int u = 1; u < uneven; u++) {
					newLine.append(" ");
					newLine.append(space);
					newLine.append(wInLine[u]);
					indexHold ++;
				}
				std::cout << indexHold;
				for (int y = indexHold; y < wInLine.size(); y++){
					newLine.append(space);
					newLine.append(wInLine[y]);
					std::cout << newLine.size() << std::endl;
				}

				lFormats.push_back(newLine);
				wInLine.clear();
				newLine.clear();
				space.clear();
				uneven*=0;
				counter*=0;
				wCount*=0;
				lSpace*=0;
			}
			
		}
	}
	for (int i = 0; i < lFormats.size(); i++){
		std::cout << "| " << lFormats[i] << " |" << std::endl;
	}
	for (int j = tLineLen; j > 0; j--) {
		std::cout << "_";
	}
	std::cout<<"\n";
}
*/

// Main code starts here: 
int main(int argc, char* argv []) {
	//getting the information from the command line
	//(argv[1]=file name, argv[3]=length limit, argv[4]=function type)
	
	int charLim = atoi(argv[3]); 
	std::cout << argv[1] << std::endl;
	// File validity check
	std::ifstream infoFile(argv[1]);
	if (!infoFile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	} 
	// Everything up to this point is good(5:06, Jan 14)
	//Open the file put all the text information into a string
	// Note to self, file contents are strings
	std::vector<std::string> info;
	std::string j;
	std::cout << j;
	while (infoFile >> j) {	info.push_back(j); }
	std::cout<<info.size()<<std::endl;
	//This line is to check if the information is transfered
	std::vector<int> wordLen;
	for (int w=0; w<info.size(); w++){
		wordLen.push_back(info[w].size());
	}
	lFlush(charLim, info, wordLen);
	justify(charLim, info, wordLen);
	//As of so far, lFlush
}

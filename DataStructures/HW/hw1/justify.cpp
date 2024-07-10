#include <iostream>
#include <fstream>
#include <vector>

// Flush left
//The function makes left alignment by 
//first adding the words to a string so it does not go over character limit
//All the excess space are kept to the left using string.append(" ");
//All formatted lines are then added to a vector before outputting it to file
void lFlush( int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	std::ofstream outfile ("output.txt");
	int tLineLen = charLim + 4; //Total length of each line
	std::string border;
	for (int j = tLineLen; j > 0; j--) {
		border+= "-";
	}
	outfile << border<< std::endl;
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
		outfile << "| " << lFormats[i] << " |" << std::endl;
	}
	outfile << border<<std::endl;
	outfile.close();
}

// Flush right
//The function makes right alignment by 
//first adding the words to a string so it does not go over character limit
//All the excess space are kept to the right using string.insert(0," ");
//All formatted lines are then added to a vector before outputting it to file
std::string rFlush(int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	std::ofstream outfile ("output.txt");
	int tLineLen = charLim + 4; //Total length of each line
	std::string border;
	for (int j = tLineLen; j > 0; j--) {
		border+="-";
	}
	outfile << border<< std::endl;
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
				newLine.insert(0, " ");
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
				newLine.insert(0," ");
			}
			if (newLine.size() == charLim){
				lFormats.push_back(newLine);
				newLine.clear();
				counter*=0;
			}
		}
	}
	for (int i = 0; i < lFormats.size(); i++){
		outfile << "|  " << lFormats[i] << "|" << std::endl;
	}
	outfile << border << std::endl;
	outfile.close();
}

// Justify
//The most tricky one, all the words are first added to a string to keep 
//each line from exceeding the character limit.
//The words and spaces are also added to a vector simultaneously
//The excess space are calculated via string.size() before properly redistributed 
//and refommated to a string.
//All formatted strings are added to a vector before outputting to the output file
void justify(int charLim, std::vector<std::string>& info, std::vector<int>& wordLen) {
	std::ofstream outfile ("output.txt");
	int tLineLen = charLim + 4; //Total length of each line
	std::string border;
	for (int j = tLineLen; j > 0; j--) {
		border+="-";
	}
	outfile << border<< std::endl;
	int counter = 0;
	int index = 0;
	int wCount = 0;
	int uneven ;
	int lSpace;
	int nSpace;
	int hold;
	std::string newLine;
	std::string dSpace;
	std::vector<std::string> lines;
	std::vector<std::string> lFormats;
	std::vector<int> positions; 

	while (index < info.size()) {
		counter += wordLen[index];
		wCount ++;
		if (index == info.size()-1 && newLine.size() < charLim){
			for (int v = 0; v < lines.size(); v++) {
				newLine.append(lines[v]);
				newLine.append(" ");
			}
			newLine.append(info[index]);
			hold = newLine.size();
			for (int n = 0; n < charLim-hold; n++) {
				newLine.append(" ");
			}
			lFormats.push_back(newLine);
			counter *= 0;
			index ++;
		} else if (counter + wCount -1 <= charLim) {
			lines.push_back(info[index]);
			index ++;
		} else {
			counter -= wordLen[index];
			wCount --;
			for (int o = 0; o < lines.size(); o ++) {
				newLine.append(lines[o]);
			}
			nSpace = charLim - newLine.size();
			lSpace = nSpace/(wCount-1);
			uneven = nSpace%(wCount-1);
			for (int t = 0; t < lSpace; t++) {
				dSpace.append(" ");
			}
			newLine.clear();
			newLine.append(lines[0]);
			for (int i = 1; i < lines.size(); i++) {
				if (i <= uneven) {
					newLine.append(" ");
					newLine.append(dSpace);
					newLine.append(lines[i]);
				}
				else{
					newLine.append(dSpace);
					newLine.append(lines[i]);
				}
			}
			lFormats.push_back(newLine);
			newLine.clear();
			lines.clear();
			dSpace.clear();
			positions.clear();
			nSpace*= 0;
			lSpace*= 0;
			counter*= 0;
			wCount*=0;
			uneven*=0;

		}
	}
	for (int i = 0; i < lFormats.size(); i++){
		outfile << "| " << lFormats[i] << " |" << std::endl;
	}
	outfile << border << std::endl;
	outfile.close();
}


// Main code starts here: 
int main(int argc, char* argv []) {
	//getting the information from the command line
	//(argv[1]=file name, argv[3]=length limit, argv[4]=function type)
	std::string outFName = argv[2];
	int charLim = atoi(argv[3]); 
	std::string commName = argv[4];
	// File validity check
	std::ifstream infoFile(argv[1]);
	if (!infoFile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	} 
	// Everything up to this point is good(5:06, Jan 14)
	//Open the file put all the text information into a string
	// Note to self, file contents are strings
	int pos = -1;
	int lenHold;
	std::vector<std::string> info;
	std::vector<int> wordLen;
	std::vector<int> lWord;
	std::string j;
	std::string longWord;
	std::vector<std::string> holder;
	std::string cut;
	while (infoFile >> j) {			
		info.push_back(j);
	}
	//This line is to check if the information is transfered
	for (int w=0; w<info.size(); w++){
		wordLen.push_back(info[w].size());
	}
	if (commName == "flush_left"){
		lFlush(charLim, info, wordLen);
	}
	else if (commName == "flush_right"){
		rFlush(charLim, info, wordLen);

	}
	else if (commName == "full_justify"){
		justify(charLim, info, wordLen);
	}
	else{
		std::cerr<<"Command invalid"<<std::endl;
		exit(1);
	}
}


#include <iostream>
#include <fstream>
#include <vector>

int main(int argc,char* argv) {
	//getting the information from the command line
	std::cout << argv << std::endl;
	std::string fileName = argv[1];
	int charLim = argv[3];
	std::string commName = argv[4];

	// File validity check
	std::ifstream in_str(fileName);
	if (!in_str.good()) {
		std::cerr << "Can't open " << fileName = argv[1] << "to read.\n";
		exit(1);
	}
	else {
		//Open the file put all the text information into a string
		std::string infoText;
		std::ifstream txtFile;
		txtFile.open("fileName");
		txtFile >> infoText;
		//This line is to check if the information is transfered
		std::cout << infoText;
	}
}
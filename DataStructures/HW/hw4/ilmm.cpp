#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "Customer.h"
#include "Tool.h"


//This following block is notes 
//Make two list, one for customer and one for inventory
//An additional list for customers that doesn't have the object in inventory
//Since cannot 
int main(int argc, char* argv []) {
	//Assign the commandline inputs to variables, convenience for later use
	std::string invFileIn = argv[1];
	std::string cusFileIn = argv[2];
	std::string invFileOut = argv[3];
	std::string cusFileOut = argv[4];
	//Check condition of the two files
	std::ifstream invFile(invFileIn);
	std::ifstream cusFile(cusFileIn);
	if (!invFile.good() || !cusFile.good()) {
		//Both files are bad
		if(!invFile.good() && !cusFile.good()) {
			std::cerr << "Can't open " << argv[1] << " and " << argv[2] << " to read.\n";
			exit(1);
		}
		//The inventory file was bad
		else if(!invFile.good()) {
			std::cerr << "Can't open " << argv[1] << " to read.\n";
			exit(1);
		}
		//The customer file was bad
		else {
			std::cerr << "Can't open " << argv[2] << " to read.\n";
			exit(1);
		}
		
	}
	else {
		cusFile.close();
		invFile.close();
		std::ifstream invFile(invFileIn);
		//Getting the content from input file
		//Making the tool objects from inventory file
		int tindex = 0;
		std::list<Tool> storage;	//This list will be our inventory list
		std::string word;
		//The following are here because we need to maintain as place holders for the in coming words
		std::string f0;
		int f1;
		std::string f2;
		while (invFile >> word) {
			//If "_" is present in a word, it is a name of the tool
			if (tindex == 0 && word.find("T") != std::string::npos) {
				f0 = word;
				tindex++;
			}
			else if (tindex == 1 && std::stoi(word) > 0) {
				f1 = std::stoi(word);
				tindex++;
			}
			else if (tindex == 2) {
				f2 = word;
				storage.push_back(Tool(f0, f1, f2));
				f0.clear();
				f1*=0;
				f2.clear();
				tindex*=0;
			}
		}
		invFile.close();
		std::cout << storage.size() << std::endl;
		//Making the customer object from customer file
		std::ifstream cusFile(cusFileIn);
		int cindex = 0;
		std::list<Customer> customers;
		std::string cword;
		std::string c0;
		std::string c1;
		int c3 = 0;
		std::string c4;
		std::string c5;
		while (cusFile>>cword) {
			if (cindex == 0 && cword.find("C") != std::string::npos) {
				c0 = cword;
				cindex++;
			}
			else if (cindex == 1) {
				c1 = cword;
				cindex++;
			}
			else if (cindex == 2) {
				cindex++;
			}
			else if (cindex == 3&&std::stoi(cword)>0) {
				c3 += std::stoi(cword);
				cindex++;
			}
			else if (cindex == 4) {
				c4 = cword;
				cindex++;
			}
			else if (cindex == 5) {
				c5 = cword;
				customers.push_back(Customer(c0, c1, c3, c4, c5));
				c0.clear();
				c1.clear();
				c3*=0;
				c4.clear();
				c5.clear();
				cindex*=0;
			}
		}
	std::cout << customers.size() << std::endl;
	
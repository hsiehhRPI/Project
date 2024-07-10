#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "Customer.h"
#include "Tool.h"

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
		std::cout << "yeet" << std::endl;
	}
	else {
		//Getting the content from input file
		//Making the tool objects from inventory file
		int tindex = 0;
		std::list<Tool> storage;	//This list will be our inventory list
		std::list<Tool>::iterator t = storage.begin();
		std::cout << storage.size() << std::endl;
		std::string word;
		//The following are here because we need to maintain as place holders for the in coming words
		std::string f0;
		int f1;
		std::string f2;
		while (invFile >> word) {
			std::cout << storage.size() << std::endl;
			//If "_" is present in a word, it is a name of the tool
			if (tindex == 0 && word.find("T") != std::string::npos) {
				f0 = word;
				tindex++;
			}
			else if (tindex == 1 && word > "0") {
				f1 = std::stoi(word);
				tindex++;
			}
			else if (tindex == 2) {
				f2 = word;
				Tool nt(f0, f1, f2);
				if (storage.size() == 0){
					storage.push_back(nt);
				}
				else{
					while (t->tGetID() < nt.tGetID()&&t!=storage.end()) {
					++t;
					}
					storage.insert(t, nt);
				}
				t = storage.begin();
				f0.clear();
				f1*=0;
				f2.clear();
				tindex*=0;
			}

		}
		std::cout << storage.size() << std::endl;
		int cindex = 0;

		std::list<Customer> customers;
		std::list<Customer>::iterator c = customers.begin(); 
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
				Customer nc(c0, c1, c3, c4, c5);
				if (storage.size() == 0){
					customers.push_back(nc);
				}
				else{
					while (c->cGetCID() < nc.cGetCID()&&c!=customers.end()) {
					++c;
					}
					customers.insert(c, nc);
				}
				c = customers.begin();
				f0.clear();
				c0.clear();
				c1.clear();
				c3*=0;
				c4.clear();
				c5.clear();
				cindex*=0;
			}
		}
	std::cout << customers.size() << std::endl;
	}
}
/*#include <iostream>
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
	//The two iterators declared here will be the iterator that moved through the list
	std::list<Tool>::iterator t_itr;
	std::list<Customer>::iterator c_itr;
	t_itr = storage.begin();
	c_itr = customers.begin();
	//The second iterator for the customer list declared here will be the anchor iterator
	//So we could return to the original position as the 
	std::list<Customer>::iterator c_main;
	c_main = customers.begin();
	//The list to keep track of people in queue waiting to get their tool
	std::list<Customer> queue;
	//Checking if the tool needed by the customer is in the storage
	long unsigned int exeIndex = 0;//This index will help keep track when the checking should stop
	long unsigned int lIndex = 0;//This index keeps track of how many customer
	while(exeIndex < storage.size()) {
		while (lIndex < customers.size()) {
			//Important note to self, *c_itr.cGetStat() is invalid because the computer will attempt to do the class 
			//function before dereferencing(which is invalid because the iterator does not have such member function).
			//To combat this problem, do c_iter->cGetStat()[recommended] or (*c_itr).cGetStat().
			if (t_itr->tGetID() == c_itr->cGetTID() && t_itr->tGetQuan() >= c_itr->cGetQuant()) {
				if (c_itr->cGetStat() == "rent") {
					t_itr->tSet_quan(t_itr->tGetQuan()-c_itr->cGetQuant());
					++c_itr;
					lIndex++;
				}
				//If people are here to return things
				else if (c_itr->cGetStat() == "return") {
					t_itr->tSet_quan(t_itr->tGetQuan()+c_itr->cGetQuant());
					c_itr->cSetState("return");
					//The queue should get priority for renting the tool than new customers
					if (queue.size() > 0) {
						for (std::list<Customer>::iterator p = customers.begin(); p != customers.end(); ++p) {
							if (t_itr->tGetID() == p->cGetTID()&&p->cGetStat() == "pending"&&t_itr->tGetQuan()>0) {
								//If the returned tool is just what the people needed, set their status back to "rent"
								if (t_itr->tGetQuan() >= p->cGetQuant()){
									p->cSetState("rent");
									t_itr->tSet_quan(t_itr->tGetQuan()-p->cGetQuant());
								}
								else if (t_itr->tGetQuan() >= p->cGetQuant()){
									p->cSetQuan(p->cGetQuant()-t_itr->tGetQuan());
									t_itr->tSet_quan(p->cGetQuant()-t_itr->tGetQuan());
								}
							}
						}
					}
					++c_itr;
					lIndex++;
				}
			}
			//The inventory did not have enough tools the customer requested
			else if (t_itr->tGetID() == c_itr->cGetTID() && t_itr->tGetQuan() < c_itr->cGetQuant()) {
				if (c_itr->cGetStat() == "rent") {
					//Scenario 1: The inventory does not have zero number of said tool
					if (t_itr->tGetQuan()==0 ) {
						c_itr->cSetState("pending");
						queue.push_back(*c_itr);
						++c_itr;
						lIndex++;
					}
					else {
					//Scenario 2: The inventory has said tool, but there isn't enough as the customers requested
						c_itr->cSetQuan(c_itr->cGetQuant() - t_itr->tGetQuan());
						t_itr->tSet_quan(0);
						c_itr->cSetState("pending");
						queue.push_back(*c_itr);
						++c_itr;
						lIndex++;
					}
				}
				//
				else if (c_itr->cGetStat() == "return") {
					t_itr->tSet_quan(t_itr->tGetQuan()+c_itr->cGetQuant());
					c_itr->cSetState("return");
					//The queue should get priority for renting the tool than new customers
					if (queue.size() > 0) {
						for (std::list<Customer>::iterator p = customers.begin(); p != customers.end(); ++p) {
							if (t_itr->tGetID() == p->cGetTID()&&p->cGetStat() == "pending"&&t_itr->tGetQuan()>0) {
								//If the returned tool is just what the people needed, set their status back to "rent"
								if (t_itr->tGetQuan() >= p->cGetQuant()){
									p->cSetState("rent");
									t_itr->tSet_quan(t_itr->tGetQuan()-p->cGetQuant());
								}
								else if (t_itr->tGetQuan() >= p->cGetQuant()){
									p->cSetQuan(p->cGetQuant()-t_itr->tGetQuan());
									t_itr->tSet_quan(p->cGetQuant()-t_itr->tGetQuan());
								}
							}
						}
					}
					++c_itr;
					lIndex++;
				}
			}
			else {
				++c_itr;
				lIndex++;
			}

		}
		std::cout << t_itr->tGetTName()<<" "<<t_itr->tGetQuan() << std::endl;
		c_itr = c_main;
		lIndex*=0;
		++t_itr;
		exeIndex++;
	}
	//Now that things are done, it is time to sort the two lists

	std::cout << queue.size() << std::endl;
	//-------------Outputs-------------
	//Outputting the inventory file
	std::ofstream cusOut (cusFileOut);
	c_itr = customers.begin();
	for (long unsigned int j = 0; j < customers.size(); j++) {
		if (c_itr->cGetStat()!="return"){
			cusOut << *c_itr << std::endl;
			++c_itr;
		}
	}

	cusOut.close();
	}
}
//Note to self: when running gdb that require input, do run and then follow by all the input files required separated by space
*/
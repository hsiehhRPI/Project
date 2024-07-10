#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <utility>

#include "miniBlast.h"

//From the given query segment of DNA(Often times it is way longer than the kmer), make the kmer associate with it
std::string makeKmer(std::string& segment, int& kmer) {
	std::string tKmer;
	for (int n = 0; n < segment.size(); n++) {
		if (tKmer.size() < kmer) {
			tKmer.push_back(segment[n]);
		}
	}
	return tKmer;
}

int main() {
//---------IMPORTANT VARIABLES -----------
int UENTRY = 0;	//Keeps track of how many unique entry is in the hash table, as of right now there are no entries
int kmer = 0;			//
//Optional arguments(information here will be overwrite if the file provide alternative information):
int tableSize = 100;	//Default to 100
float occupancy = 0.65;	//Default to 0.65
//------------------------------------
	//Get all of the information inside the input file into a vector to parse for later
	std::vector<std::string> queryInfo;
	std::string info;
	while (std::cin>>info) {
		queryInfo.push_back(info);
	}
	//Parsing the information inside the query file:
	//Some metrics we will definitely need:
	std::string genome;		//Which genome database file we will be reading from later
	for (int n = 0; n < queryInfo.size(); n++) {
		if (queryInfo[n].find(".txt") != std::string::npos) {
			//If current element contain the file name of the genomic database
			genome = queryInfo[n];
		}
		if (queryInfo[n].find("table_size")!=std::string::npos) {
			tableSize = stoi(queryInfo[n+1]);
		}
		if (queryInfo[n].find("occupancy")!=std::string::npos) {
			occupancy = stof(queryInfo[n+1]);
		}
		if (queryInfo[n].find("kmer")!=std::string::npos) {
			kmer = stoi(queryInfo[n+1]);
		}
	}
	
	//Getting inputting information from the genome file into the hash table
	std::ifstream genomeDB(genome);
	char nitroBase;
	std::string library;		//This is a huge string that contain all the information given by the input file
	while (genomeDB >> nitroBase) {
		library.push_back(nitroBase);
	}
	//Create the hash table
	hashTB LocLib(tableSize);
	//Inputting all these information into the hash table(cutting each piece into the size of kmer)
	for (int y = 0; y < library.size()-(kmer-1); y++) {	
		//We minus the size of the table is because of the elements at the end would not be able to form designated length kmers
		std::string knome;
		//Creating segments of code with length kmer
		for (int x = y; knome.size() < kmer; x++) {
			knome.push_back(library[x]);
		}
		LocLib.insert(knome, y, occupancy);
	}
	
	//Now that everything is hashed into the table, time to search for each query
	int mismatch = 0;		//The number of allowed mismatch
	std::string target;	//The segment of DNA we are trying to find
	std::string tKmer;
	for (int y = 0; y < queryInfo.size(); y++) {
		if (queryInfo[y]=="quit") {
			break;
		}
		if (queryInfo[y]=="query") {
			mismatch = stoi(queryInfo[y+1]);
			target = queryInfo[y+2];
			tKmer = makeKmer(target, kmer);
			std::vector<std::vector<int>> searchRes = LocLib.find(tKmer, target, library, mismatch);
			//Output the result via cout as we go along
			std::cout << "Query: " ;
			std::cout << target << std::endl;
			if (searchRes.size() == 0) {
				std::cout << "No Match" << std::endl;
			}
			else {
				//Prepare the result segment of DNA
				std::string TSegment;
				for (int n = 0; n < searchRes.size(); n++) {
					for (int x = searchRes[n][0]; x < (searchRes[n][0]+target.size()); x++) {
						TSegment.push_back(library[x]);
					}
					std::string strLoc = std::to_string(searchRes[n][0]);
					std::string strMS = std::to_string(searchRes[n][1]);
					std::cout << strLoc << " " ;
					std::cout << strMS << " " ;
					std::cout <<TSegment<<std::endl;
					TSegment.clear();
				}
			}
		}
	}


}
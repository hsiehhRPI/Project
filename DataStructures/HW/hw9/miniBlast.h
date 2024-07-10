//The code is largely based on the ds_hashset given in lab 11.
//However, it is rewritten to be 2D vector instead of vector of lists
#ifndef __miniBlast_h_
#define __miniBlast_h_

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class hashTB {
public:
	//CONSTRUCTOR
	//Function to create a hash table
hashTB (int tSize) {
	std::vector<std::pair<std::string, int> > t;
	for (int n = 0; n < tSize; n++) {
		std::pair<std::string, int> tmp;
		tmp.first = " ";
		tmp.second = -1;
		t.push_back(tmp);
	}
	table = t;
	uEntry = 0;

}

//Hash function
unsigned int hashIt ( const std::string& key ) {
    //  This part of code is also borrowed from lab 11
    //  http://www.partow.net/programming/hashfunctions/
    //
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
}   

//Function that resize the table
void resize(long unsigned int nSize) {
	//Create an empty vector with the new size by pushing back whitespace as place holders
	std::vector<std::pair<std::string, int>> nVec;
	for (int n = 0; n < nSize; n++) {
		std::pair<std::string, int> tmp;
		tmp.first = " ";
		tmp.second = -1;
		nVec.push_back(tmp);
	}
	//Rehash each value, since the index after hashing is dependent on the size of the vector
	for (int v = 0; v < table.size(); v++) {
		//If there is a value, re-hash it
		if (table[v].first!=" ") {
			unsigned int hashV = hashIt(table[v].first);
			unsigned int idx = hashV%nVec.size();
			if (nVec[idx].first==" ") {
				//If the location in the new vector is empty
				nVec[idx]=table[v];
			}
			else {
				for (int g = 1; g < 30; g++) {
					if (nVec[idx+g].first==" ") {
						nVec[idx+g]=table[v];
						break;
					}
				}
			}
		}
	}
	table = nVec;
}
//Insert function:
void insert(std::string& knome, int& location, float& occupancy) {
	//Check if the table needs to be resize(if unique entry/size of table)
	float curOcc = uEntry;
	curOcc /= table.size();
	if (curOcc >= occupancy) {
		resize(2*table.size());
	}
	unsigned int hashV = hashIt(knome);
	unsigned int idx = hashV%table.size();
	if (table[idx].first==" ") {
		table[idx].first = knome;
		table[idx].second = location;
		uEntry++;
		return;
	}
	else {
		//Linear probing: if this location is taken, go until when 
		for (int n = 1; n < 30; n++) {
			if (table[idx+n].first==" "&&idx+n<(table.size()-1)) {
				table[idx+n].first = knome;
				table[idx+n].second = location;
				uEntry++;
				return;
			}
		}
	}
}

//Helper function of the find function below
//Check if the segment of DNA at said position is similar enough to the one in the query
//If the amount of mismatch is within a reasonable range, return the given index and also the number of mismatch
//If the amount of mismatch is too much, return a vector containing number -1, indicating it is not the result
std::vector<int> checkSame(std::string& target, int idx, std::string& library, int& mismatch) {
	int count = 0;	//Keeps track of actual mismatch
	int wInc = 0;		//Keeps track of indexing the query segment
	//Step through the library to see if it is the same as the query segment
	for (int n = idx; n < (idx+target.size()); n++) {
		if (library[n]!=target[wInc]) {
			count++;
		}
		wInc++;
	}
	std::vector<int> result;
	//If there is less than or equal amount of mismatch as the given acceptable value
	if (count <= mismatch) {
		result.push_back(idx);
		result.push_back(count);
		return result;
	}
	else {
		//There are too much mismatch
		result.push_back(-1);
		return result;
	}

}

//Find function:
std::vector<std::vector<int>> find(std::string& knome, std::string& target, std::string& library, int& mismatch) {
	//Hash the knome that is made from the target segment of DNA
	unsigned int hashV = hashIt(knome);
	unsigned int idx = hashV%table.size();
	int next = 0;
	std::vector<std::vector<int>> result;
	//Because there may be repeat of knome throughout the library string, we should stop when a white space is hit or the query is found
	while (table[idx+next].first!=" ") {
		std::vector<int> candidate = checkSame(target, table[idx+next].second, library, mismatch);
		//If the result is correct and found, to accommodate multiple correct result, we push_back the correct solutions
		if (candidate.size()>1) {
			result.push_back(candidate);
		}
		next++;
	}
	return result;		//If the result is not found, then an empty vector is returned
}

void printResult(std::string& target,std::vector<int>& result, std::string& locSeg) {
	std::cout << "Query: " << target << std::endl;
	if (result.size()==0) {
		std::cout << "No Match" << std::endl;
		return;
	}
	else {
		std::cout << std::to_string(result[0]) << " " << std::to_string(result[1]) << " " << locSeg <<std::endl;
		return;
	}
}

private:
	std::vector <std::pair<std::string, int> > table;
	int uEntry;
};
#endif
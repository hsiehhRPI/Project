#include <string>
//You may add additional typedefs, includes, etc. up here
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include "Fighter.h"

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

//This is a helper function for the following two functions. The argument given will be in the format<fighter name, frame of specified move>
//Since the output needs to be sorted by frame instead of fighter name, 
//we are going to flip key and value and format into a map by <int, std::set<std::string> > instead where it is <frame number, set of fighters with said frame>

std::map<int, std::set<std::string> > flipKeyVal (std::map<std::string, std::string> intermediate) {
	std::map<int, std::set<std::string> > flipped;
	std::map<std::string, std::string>::iterator ytr;
	for (ytr = intermediate.begin(); ytr != intermediate.end(); ++ytr) {
		flipped[stoi(ytr->second)].insert(ytr->first);
	}
	return flipped;
}

//This function goes through the given move compendiums and add them into a std::map<std::string, std::string> first
//To track the number of fighters added, the map is gonna be in the format <name of fighter, frame> first(since name of the fighters are unique, but not the frame number)
//Once there are enough fighters added, flipKeyVal is called to return the map in std::map<int, std::set<std::string> > instead(so the sorting will be by frame number and not fighter's name)
std::map<int, std::set<std::string> > findFastestFrame (std::map<int, std::set<std::string> >& moveComp, int fLimit){
	if (fLimit == 0) {
		//If the given number is 0, we should have no fighters
		std::map<int, std::set<std::string> >none;
		return none;
	}
	else {
		std::map<std::string, std::string> fastestFighter;
		std::map<int, std::set<std::string> >::iterator mtr = moveComp.begin();
		int count = 0;
		for (mtr; mtr != moveComp.end(); ++mtr) {
			for (std::set<std::string>::iterator itr = mtr->second.begin(); itr != mtr->second.end(); ++itr) {
				count ++;
				if (fastestFighter.size() < fLimit) {
					fastestFighter[*itr] = std::to_string(mtr->first);
				}
				else {
					std::map<int, std::set<std::string> > fixed = flipKeyVal(fastestFighter);
					return fixed;
				}
			}
		}
	}
}

//It is essentially the same function as the one above, except the iterator is assigned to the end and decrimented to find the slowest frames instead
std::map<int, std::set<std::string> > findSlowestFrame (std::map<int, std::set<std::string> >& moveComp, int fLimit){
	if (fLimit == 0) {
		//If the given number is 0, we should have no fighters
		std::map<int, std::set<std::string> >none;
		return none;
	}
	else {
		std::map<std::string, std::string> slowestFighters;	//This is our intermediate map that contain elements in format <fighter, frame>
		std::map<int, std::set<std::string> >::iterator mtr = moveComp.end();
		int count = 0;
		--mtr;		//Have to do this because there is no value at moveComp.end();
		for (mtr; mtr != moveComp.begin(); --mtr) {
			for (std::set<std::string>::iterator itr = mtr->second.begin(); itr != mtr->second.end(); ++itr) {
				count ++;
				if (slowestFighters.size() < fLimit) {					//If there should be more fighters added 
					slowestFighters[*itr] = std::to_string(mtr->first);
				}
				else {
					std::map<int, std::set<std::string> > fixed = flipKeyVal(slowestFighters);
					return fixed;
				}
			}
		}
	}
}

int main(int argc, char** argv){
	// Argument parsing
	std::string db = argv[1];
	std::string inFile = argv[2];
	std::string outFile = argv[3];
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(db);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(inFile);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(outFile);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	///////Fill in the rest of main below:

	//This will be our database file
	std::map<std::string, class Fighter> FightersCompendium;

	//The arguments needed to construct the fighter class
	std::string fighter;
	std::string jab_;
	std::string fTilt_;
	std::string uTilt_;
	std::string dTilt_;
	std::string fSmash_;
	std::string uSmash_;
	std::string dSmash_;

	//Getting information from the database file and putting them in the fighters compendium
	while (dbfile >> fighter >> jab_ >>fTilt_>>uTilt_>>dTilt_>>fSmash_>>uSmash_>>dSmash_) {
		//Adding all the fighters into the map by using the fighter's name as key, Fighter object of the character as the value
		FightersCompendium[fighter] = Fighter(fighter, jab_, fTilt_, uTilt_, dTilt_, fSmash_, uSmash_, dSmash_);
	}
	FightersCompendium.erase("character-name");

	//Making different compendiums for later use
	//(since there are searches for slowest/fasted frame characters, might as well just do it now)
	//These are the compendiums for each move, which will contain the frame and the name of the character
	//The key will be the frame of the move, the value is a set containing names of the Fighter with moves with said frame number
	std::map<int, std::set<std::string> > DSmashComp;
	std::map<int, std::set<std::string> > DTiltComp;
	std::map<int, std::set<std::string> > FSmashComp;
	std::map<int, std::set<std::string> > FTiltComp;
	std::map<int, std::set<std::string> > JabComp;
	std::map<int, std::set<std::string> > USmashComp;
	std::map<int, std::set<std::string> > UTiltComp;

	//Adding the values into each move compendiums
	std::map<std::string, class Fighter>::iterator track;
	for (track = FightersCompendium.begin(); track!=FightersCompendium.end(); ++track) {
		DSmashComp[stoi(track->second.getDSmash())].insert(track->first);
		DTiltComp[stoi(track->second.getDTilt())].insert(track->first);
		FSmashComp[stoi(track->second.getFSmash())].insert(track->first);
		FTiltComp[stoi(track->second.getFTilt())].insert(track->first);
		JabComp[stoi(track->second.getJab())].insert(track->first);
		USmashComp[stoi(track->second.getUSmash())].insert(track->first);
		UTiltComp[stoi(track->second.getUTilt())].insert(track->first);
	}

	//Getting all the information from the query file
	std::vector<std::string> queryInfo;
	std::string info;
	while (infile >> info) {
		queryInfo.push_back(info);
	}

	//There are going to be some conversion from string to intgers(to be inputted into the function written above)
	//There are also conversion of integer to strings for outputting to a file(which had to be in std::string format)
	for (long unsigned int y = 0; y < queryInfo.size(); y++) {
		if (queryInfo[y] == "-q") {
			//For the command -q, we are given a character's name instead of a frame, so we are gonna use the fighters compendium
			std::map<std::string, class Fighter>::iterator finder = FightersCompendium.find(queryInfo[y+1]);
			if (finder == FightersCompendium.end()) {
				//This name is not in our database, it will be outputted as invalid character
				outfile << "Invalid character name: " << queryInfo[y+1] << std::endl;
			}
			else {
				if (queryInfo[y+2] == "all") {
					outfile << finder->first << " " << "down-smash: " << finder->second.getDSmash()<<std::endl;
					outfile << finder->first << " " << "down-tilt: " << finder->second.getDTilt()<<std::endl;
					outfile << finder->first << " " << "forward-smash: " << finder->second.getFSmash()<<std::endl;
					outfile << finder->first << " " << "forward-tilt: " << finder->second.getFTilt()<<std::endl;
					outfile << finder->first << " " << "jab: " << finder->second.getJab()<<std::endl;
					outfile << finder->first << " " << "up-smash: " << finder->second.getUSmash()<<std::endl;
					outfile << finder->first << " " << "up-tilt: " << finder->second.getUTilt()<<std::endl;
				}
				else {
					//If the query only calls for one specific move
					if (queryInfo[y+2] == "down-smash") {
						outfile << finder->first << " " << "down-smash: " << finder->second.getDSmash()<<std::endl;
					}
					else if (queryInfo[y+2] == "down-tilt") {
						outfile << finder->first << " " << "down-tilt: " << finder->second.getDTilt()<<std::endl;
					}
					else if (queryInfo[y+2] == "forward-smash") {
						outfile << finder->first << " " << "forward-smash: " << finder->second.getFSmash()<<std::endl;
					}
					else if (queryInfo[y+2] == "forward-tilt") {
						outfile << finder->first << " " << "forward-tilt: " << finder->second.getFTilt()<<std::endl;
					}
					else if (queryInfo[y+2] == "jab") {
						outfile << finder->first << " " << "jab: " << finder->second.getJab()<<std::endl;
					}
					else if (queryInfo[y+2] == "up-smash") {
						outfile << finder->first << " " << "up-smash: " << finder->second.getUSmash()<<std::endl;
					}
					else if (queryInfo[y+2] == "up-tilt") {
						outfile << finder->first << " " << "up-tilt: " << finder->second.getUTilt()<<std::endl;
					}
					else {
						//If it is not in the compendium, that means it is not a proper move
						outfile << "Invalid move name: " << queryInfo[y+2] << std::endl;
					}
				}
			}
			outfile << std::endl;
		}
		if (queryInfo[y] == "-f") {
			outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
			//Each of the following if/else if conditions are to check which of the move compendium I should use
			if (queryInfo[y+1] == "down-smash") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(DSmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {//Iterate through the map, does not account for the sets that are the value of the map
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {	//str goes through the set to grab the name individual fighters 
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			else if (queryInfo[y+1] == "down-tilt") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(DTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			else if (queryInfo[y+1] == "forward-smash") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(FSmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}	
			else if (queryInfo[y+1] == "forward-tilt") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(FTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			else if (queryInfo[y+1] == "jab") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(JabComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			else if (queryInfo[y+1] == "up-smash") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(USmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			else if (queryInfo[y+1] == "up-tilt") {
				std::map<int, std::set<std::string> > targetFighters = findFastestFrame(UTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.begin();
				for (otr = targetFighters.begin(); otr!=targetFighters.end(); ++otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
			}
			
			else {
				outfile << "Invalid move name: " << queryInfo[y+1] << std::endl;
			}
			outfile << std::endl;

		}
		if (queryInfo[y] == "-s") {
			//Each of the following if/else if conditions are to check which of the move compendium I should use
			if (queryInfo[y+1] == "down-smash") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(DSmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {//Iterate through the map, does not account for the sets that are the value of the map
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {	//To go into the sets and grab the characters
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else if (queryInfo[y+1] == "down-tilt") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(DTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else if (queryInfo[y+1] == "forward-smash") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(FSmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}	
			else if (queryInfo[y+1] == "forward-tilt") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(FTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else if (queryInfo[y+1] == "jab") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(JabComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else if (queryInfo[y+1] == "up-smash") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(USmashComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else if (queryInfo[y+1] == "up-tilt") {
				outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
				std::map<int, std::set<std::string> > targetFighters = findSlowestFrame(UTiltComp, stoi(queryInfo[y+2]));
				std::map<int, std::set<std::string> >::iterator otr = targetFighters.end();
				otr --;
				for (otr; otr!=targetFighters.begin(); --otr) {
					for (std::set<std::string>::iterator str = otr->second.begin(); str!=otr->second.end(); ++str) {
						outfile << *str << " " << std::to_string(otr->first) << std::endl;
					}
				}
				for (std::set<std::string>::iterator x = otr->second.begin(); x != otr->second.end(); ++x) {
					outfile<< *x << " " << std::to_string(otr->first)<<std::endl;
				}
			}
			else {
				outfile << "Invalid move name: " << queryInfo[y+1] << std::endl;
			}
			outfile << std::endl;

		}
		if (queryInfo[y] == "-d") {
			outfile << queryInfo[y] << " " << queryInfo[y+1] << " " << queryInfo[y+2] << std::endl;
			//Search for which move compendium we are going to use
			if (queryInfo[y+1] == "down-smash") {
				std::map<int, std::set<std::string> >::const_iterator sF = DSmashComp.begin();
				for (sF = DSmashComp.begin(); sF != DSmashComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;	//Had to use an iterator because sets cannot be indexed
						}
					}
				}
			}
			else if (queryInfo[y+1] == "down-tilt") {
				std::map<int, std::set<std::string> >::const_iterator sF = DTiltComp.begin();
				for (sF = DTiltComp.begin(); sF != DTiltComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}
			else if (queryInfo[y+1] == "forward-smash") {
				std::map<int, std::set<std::string> >::const_iterator sF = FSmashComp.begin();
				for (sF = FSmashComp.begin(); sF != FSmashComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}	
			else if (queryInfo[y+1] == "forward-tilt") {
				std::map<int, std::set<std::string> >::const_iterator sF = FTiltComp.begin();
				for (sF = FTiltComp.begin(); sF != FTiltComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}
			else if (queryInfo[y+1] == "jab") {
				std::map<int, std::set<std::string> >::const_iterator sF = JabComp.begin();
				for (sF = JabComp.begin(); sF != JabComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}
			else if (queryInfo[y+1] == "up-smash") {
				std::map<int, std::set<std::string> >::const_iterator sF = USmashComp.begin();
				for (sF = USmashComp.begin(); sF != USmashComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}
			else if (queryInfo[y+1] == "up-tilt") {
				std::map<int, std::set<std::string> >::const_iterator sF = UTiltComp.begin();
				for (sF = UTiltComp.begin(); sF != UTiltComp.end(); ++sF) {
					if (sF->first == stoi(queryInfo[y+2])) {
						for (std::set<std::string>::iterator f = sF->second.begin(); f != sF->second.end(); ++f) {
						outfile << *f << std::endl;
						}
					}
				}
			}
			else {
				outfile << "Invalid move name: " << queryInfo[y+1] << std::endl;
			}
			outfile << std::endl;
		}
	}
	return 0;
}

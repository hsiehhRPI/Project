#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "players.h"
#include "schools.h"
#include "penalties.h"

int main(int argc, char* argv []) {
	std::string fileName = argv[1];
	std::string outFile = argv[2];
	std::string status = argv[3];

	//Check if file condition is good
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	//(For player class)First weedout, only getting the lines with player information by checking if "_" is present
	std::vector<std::string> eachLine;
	std::string inLine;
	while (inFile>>inLine){
		eachLine.push_back(inLine);
	}
	//Second weedout, creating a list of players and schools
	std::vector<std::string> schl_player;			//This is our general vector, containing all the stuff we need
	std::vector<std::string> penScore; 				//This vector will be specifically for the school class
	std::vector<std::string> pName;					
	std::vector<std::string> sName;
	std::string schoolHolder;
	int pCount = 0;
	for (int e = 0; e < eachLine.size(); e++) {
		if (e>0==true) {
			if (eachLine[e-1].find(":") != std::string::npos&&eachLine[e-1] != "2:00"&&eachLine[e-1] != "10:00"&&eachLine[e-1] != "5:00") {
				schoolHolder = eachLine[e];
				schl_player.push_back(eachLine[e]);
				penScore.push_back(eachLine[e]);
				sName.push_back(eachLine[e]);
			}
			else if (eachLine[e] == "goal") {
				schl_player.push_back(eachLine[e]);
				penScore.push_back(eachLine[e]);
			}
			else if (eachLine[e] == "penalty"){
				schl_player.push_back(eachLine[e]);
				penScore.push_back(eachLine[e]);
				pCount += 1;
			}
			else if (eachLine[e].find("._") != std::string::npos && eachLine[e+1]=="penalty"||eachLine[e+1]=="goal") {
				continue;
			}
			else if (eachLine[e].find("_") != std::string::npos&&eachLine[e-1].find(":")==std::string::npos) {
				schl_player.push_back(eachLine[e]);
				pName.push_back(eachLine[e]);
				pName.push_back(schoolHolder);
			}
		}
	}

	std::vector<std::string> uSchool;	
	for (int t = 0; t < sName.size(); t++) {
		if (std::find(uSchool.begin(), uSchool.end(), sName[t]) == uSchool.end()) {
			uSchool.push_back(sName[t]);
		}
	}
	std::vector<std::string> uPlay;
	for (int b = 0; b < pName.size(); b++) {
		if (pName[b].find("_") != std::string::npos) {
			if (std::find(uPlay.begin(), uPlay.end(), pName[b]) == uPlay.end()) {
				uPlay.push_back(pName[b]);
				uPlay.push_back(pName[b+1]);
			}
		}
	}
	//Creating players from the players class & creating schools from school class
	std::vector<School> uni;
	std::vector<Players> athlete; 
	for (int p = 0; p < uPlay.size()-1; p++) {
		if (uPlay[p].find("_.") == std::string::npos && uPlay[p].find("_") != std::string::npos){
			athlete.push_back(Players(uPlay[p], uPlay[p+1]));
		}
		p++;
	}
	for (int s = 0; s < uSchool.size(); s++) {
		uni.push_back(School(uSchool[s]));
	}

	//(For the players) filling in the goals, penalties
	int index = 0;
	while (index < athlete.size()) {
		for (int r = 0; r < schl_player.size(); r++) {
			if (r > 0 == true) {
				if (athlete[index].getName() == schl_player[r]) {
					if (schl_player[r-1] == "penalty") {
						athlete[index].set_penal(athlete[index].getPenal()+1);
					}
					else if(schl_player[r-1] == "goal") {
						athlete[index].set_goal(athlete[index].getGoal()+1);

					}
					else if(schl_player[r-1].find("(") != std::string::npos || schl_player[r-1].find("_") != std::string::npos) {
						athlete[index].set_assist(athlete[index].getAssist()+1);
					}
				}
			}
		}
		index++;
	}

	//(For the schools) filling in the goals, penalties
	int sindex = 0;
	while (sindex < uni.size()) {
		for (int a = 0; a < eachLine.size()+1; a++) {
			if (uni[sindex].getSName() == eachLine[a]) {
				if (eachLine[a+1] == "penalty") {
					uni[sindex].set_Spenalty(uni[sindex].getSPenalty()+1);
				}
				else if (eachLine[a+1] == "goal") {
					uni[sindex].set_Sgoal(uni[sindex].getSGoal()+1);
				}
			}
		}
		sindex ++;
	}

	//Get wins and lose 
	std::vector<std::string> scores;
	for (int x = 0; x < eachLine.size(); x++) {
		if (eachLine[x] == "FINAL") {
			scores.push_back(eachLine[x+1]);
			scores.push_back(eachLine[x+2]);
			scores.push_back(eachLine[x+3]);
			scores.push_back(eachLine[x+4]);
		}
	}
	std::vector<std::string> totalWin;
	std::vector<std::string> totalLose;
	std::vector<std::string> totalTies;
	for (int w = 1; w<scores.size(); w++) {
		if (scores[w].size() == 1) {
			if (scores[w] > scores[w+2]) {
				totalWin.push_back(scores[w-1]);
				totalLose.push_back(scores[w+1]);
			}
			else if (scores[w] < scores[w+2]) {
				totalWin.push_back(scores[w+1]);
				totalLose.push_back(scores[w-1]);
			}
			else if (scores[w] == scores[w+2]) {
				totalTies.push_back(scores[w+1]);
				totalTies.push_back(scores[w-1]);
			}

		}
		w+=3;
	}
	int wIndex = 0;
	while (wIndex < uni.size()) {
		for (int f = 0; f < totalWin.size(); f++) {
			if (totalWin[f] == uni[wIndex].getSName()) {
				uni[wIndex].set_Swins(uni[wIndex].getSWin()+1);
			}
			else if (totalLose[f] == uni[wIndex].getSName()) {
				uni[wIndex].set_Sloses(uni[wIndex].getSLose()+1);
			}
		}
		for (int l = 0; l < totalTies.size(); l++) {
				uni[wIndex].set_Sties(uni[wIndex].getSTies()+1);
		}
		wIndex++;
	}

	//Adding each team's win rate;
	for (int d = 0 ; d < uni.size(); d++) {
		uni[d].set_winRate(uni[d].calcWinRate());
	}
	//Sorting for the schools
	sort(uni.begin(), uni.end(), isOnTop);
	
	//Sorting for the players
	sort(athlete.begin(), athlete.end(), isInFront);

	//Dealing with interesting information
	std::vector<std::string> typesOfPenal;
	std::vector<std::string> timeOut;
	std::vector<std::string> teamPenal;
	for (int g = 0; g < eachLine.size()-1; g++) {
		if (eachLine[g] == "penalty") {
			teamPenal.push_back(eachLine[g-1]);
		}
		else if (eachLine[g].find(":") != std::string::npos && eachLine[g+1].find("_") != std::string::npos) {
			teamPenal.push_back(eachLine[g+1]);
			teamPenal.push_back(eachLine[g]);
			typesOfPenal.push_back(eachLine[g+1]);
			timeOut.push_back(eachLine[g]);
		}
	}	
		//Getting the total time of time out given in this season
	int totalTimeout = 0;
	for (int f = 0; f < timeOut.size(); f++) {
		if (timeOut[f] == "2:00") {
			totalTimeout += 2;
		}
		else if (timeOut[f] == "5:00") {
			totalTimeout += 5;
		}
		else if (timeOut[f] == "10:00") {
			totalTimeout += 10;
		}
	}
		//Create different penality class
	std::vector<Penalties> ruleBreak;
	for (int y = 0; y < uSchool.size(); y++) {
		ruleBreak.push_back(Penalties(uSchool[y]));
	}

	int pIndex = 0;
	//Getting the penalty time of each school
	while (pIndex < ruleBreak.size()) {
		for (int d = 0; d < teamPenal.size(); d++) {
			if (teamPenal[d] == ruleBreak[pIndex].getT()) {
				if (teamPenal[d+2] == "2:00") {
					ruleBreak[pIndex].set_TeamPenal(ruleBreak[pIndex].getTeamPenal()+2);
				}
				else if (teamPenal[d+2] == "5:00") {
					ruleBreak[pIndex].set_TeamPenal(ruleBreak[pIndex].getTeamPenal()+5);
				}
				else if (teamPenal[d+1] == "10:00") {
					ruleBreak[pIndex].set_TeamPenal(ruleBreak[pIndex].getTeamPenal()+10);
				}
			}
		}
		pIndex ++;
	}

		//Narrow it down so only one of each type of penalty is present
		std::vector<std::string> tPenal;
		for (int y = 0; y < typesOfPenal.size(); y ++) {
			if (std::find(tPenal.begin(), tPenal.end(), typesOfPenal[y]) == tPenal.end()) {
				tPenal.push_back(typesOfPenal[y]);
				tPenal.push_back(typesOfPenal[y+1]);
			}
		}
		std::vector<int> counts;
		int tIndex = 0;
		int nP; 
		sort(tPenal.begin(), tPenal.end());
		while (tIndex<tPenal.size()){
			for (int x = 0; x < typesOfPenal.size(); x ++) {
				if (tPenal[tIndex] == typesOfPenal[x]){
					nP ++;
				}
			}
			counts.push_back(nP);
			nP*=0;
			tIndex++;
		}
		//This is the rarest penalty
		int pos = std::distance(std::begin(counts), std::min_element(std::begin(counts), std::end(counts)));
		int minimum = counts[pos];
		

	//Formatting the schools table
	if (status == "--team_stats") {
		std::ofstream outfile (argv[2]);
		int maxSname = 0;
		for (int m = 0; m < uni.size(); m++) {
			if (uni[m].getSName().size() > maxSname) {
				maxSname = uni[m].getSName().size();
			}
		}
		
		outfile << std::setw(15)<<std::left << "Team Name";
		outfile << std::setw(2)<<std::right<<"W";
		outfile << std::setw(4)<<std::right<< "L";
		outfile << std::setw(4)<<std::right << "T";
		outfile << std::setw(7)<<std::right << "Win%";
		outfile << std::setw(7) <<std::right<< "Goals";
		outfile << std::setw(11)<<std::right << "Penalties"<<std::endl;
		//Up to this part, stuff are okay, but not others
		for (int h = 0; h < uni.size(); h++) {
			outfile << uni[h];
		}
		outfile.close();
	}
	//Formatting the table for players
	else if (status == "--player_stats") {
		std::ofstream outfile (argv[2]);
		int maxName = 0;
		for (int m = 0; m < athlete.size(); m++) {
			if (athlete[m].getName().size() > maxName) {
				maxName = athlete[m].getName().size();
			}
		}
		int maxSname = 0;
		for (int m = 0; m < uni.size(); m++) {
			if (uni[m].getSName().size() > maxSname) {
				maxSname = uni[m].getSName().size();
			}
		}
		outfile <<std::setw(maxName+2)<<std::left << "Player Name";
		outfile <<std::setw(maxSname+3) << std::left << "Team";
		outfile << std::setw(7) <<std::left << "Goals";
		outfile << std::setw(9) <<std::left << "Assists";
		outfile << std::left << "Penalties"<<std::endl;

		for (int h = 0; h < athlete.size(); h++) {
			outfile << athlete[h];
		}
		outfile.close();
}
	// Getting the more interesting statistics(custom)
		std::ofstream outfile (argv[2]);
		outfile <<std::setw(10 + 3);
		outfile<<std::left <<"Team Name";
		outfile<<std::setw(12 + 3);
		outfile<<std::left <<"Penalty Time"<<std::endl;
		for (int n = 0; n < ruleBreak.size(); n++) {
			outfile << ruleBreak[n];
		}
		outfile.close();

}
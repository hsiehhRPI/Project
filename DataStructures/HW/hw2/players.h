//FILE: players.h
#ifndef __players_h_
#define __players_h_
#include <string>
#include <vector>
#include <iostream>

//This class keeps track of each player's goals ,assist ,and penalties

class Players {
public: 
	//CONSTRUCTORS
	Players(std::string nName_="", std::string uName=""/*, int goal_, int assist_, int penalty_*/);
	
	//ACCESSORS
	std::string getName() const;
	std::string getUni() const;
	int getGoal() const;
	int getAssist() const;
	int getPenal() const;

	//MODIFIERS
	void set_goal(int goal);
	void set_assist(int assist);
	void set_penal(int penalty);

private:
	//REPRESENTATION
	std::string name, uni;
	int goals;
	int assists;
	int penalties;
}; 
//NON-MEMBER FUNCTIONS
bool isInFront (const Players& p1, const Players& p2);					//To sort players goals + assist > penalties
std::ostream& operator<<(std::ostream& ostr, const Players &p);			//To output to a file 
#endif

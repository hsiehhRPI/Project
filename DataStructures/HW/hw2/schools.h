//FILE: schools.h
#ifndef __schools_h_
#define __schools_h_

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

//This class keeps track of each team's performance, such as wins, lose, win rate, goals, and penalties


class School {
public: 
	//CONSTRUCTOR
	School(std::string name_="");

	//ACCESSORS
	std::string getSName() const;
	int getSPenalty() const;
	int getSGoal() const;
	int getSWin() const;
	int getSLose() const;
	int getSTies() const;
	float getSWinRate() const;
	int getPenTime() const;
	float getpTO() const;

	//MODIFIERS
	void set_Sgoal(int agoal);
	void set_Spenalty(int apenalty);
	void set_Swins(int awin);
	void set_Sloses(int alose);
	void set_Sties(int atie);
	void set_winRate(float awinR);
	void set_PenTime(int ahour);
	void set_pTimout(float tTimeOut);

	// OTHER FUNCTIONS
	float calcWinRate();

private:
	std::string Sname;
	int Spenalty;
	int Sgoal;
	int Swin;
	int Slose;
	int Stie;
	float SwinRate;
	int PenTime;
	float pTO;
};
bool isOnTop(const School& s1, const School& s2);				//Sort by best winrate > goals > alphabetical order
std::ostream& operator<<(std::ostream& ostr, const School &s);
#endif

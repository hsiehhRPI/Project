#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "schools.h"

//Default constructor
School::School(std::string name_) {
	Sname = name_;
	Sgoal = 0;
	Spenalty = 0;
	Swin = 0; 
	Slose = 0;
	Stie = 0;
	SwinRate = 0;
	PenTime = 0;
	pTO=0;
}
//Accessor functions
std::string School::getSName() const {
	return Sname;
}
int School::getSPenalty() const {
	return Spenalty;
}
int School::getSGoal() const {
	return Sgoal;
}
int School::getSWin() const {
	return Swin;
}
int School::getSLose() const {
	return Slose;
}
int School::getSTies() const {
	return Stie;
}
float School::getSWinRate() const {
	return SwinRate;
}
int School::getPenTime() const {
	return PenTime;
}
float School::getpTO() const {
	return pTO;
}


//Modifier functions
void School::set_Sgoal(int agoal) {
	Sgoal = agoal;
}

void School::set_Spenalty(int apenalty) {
	Spenalty = apenalty;
}
void School::set_Swins(int awin) {
	Swin = awin;
}
void School::set_Sloses(int alose) {
	Slose = alose;
}
void School::set_Sties(int atie) {
	Stie = atie;
}
void School::set_winRate(float awinR) {
	SwinRate = awinR;
}
void School::set_PenTime(int ahour) {
	PenTime = ahour;
}
void School::set_pTimout(float cPTO) {
	pTO = cPTO;
}


//Other functions
float School::calcWinRate() {
	float aWinR = (Swin+ 0.5*Stie)/(Swin+Slose+Stie);
	return aWinR;
}

//None Member Function
bool isOnTop(const School& s1, const School& s2) {
	if (s1.getSWinRate() > s2.getSWinRate()) {
		return true;
	}
	else if (s1.getSWinRate() < s2.getSWinRate()) {
		return false;
	}
	else {

		if (s1.getSGoal() > s2.getSGoal()) {
			return true;
		}
		else if (s1.getSGoal() < s2.getSGoal()) {
			return false;
		}
		else {
			if (s1.getSName() < s2.getSName()) {
				return true;
			}
			else if (s1.getSName() < s2.getSName()) {
				return false;
			}
		}
	}
}
std::ostream& operator<< (std::ostream& ostr, const School& s) {
	ostr << std::setw(15) << std::left << s.getSName() << std::setw(2) << std::right << s.getSWin();
	ostr << std::setw(4) << std::right << s.getSLose() << std::setw(4) << std::right << s.getSTies();
	ostr << std::setw(7) << std::right <<std::setprecision(2)<<std::fixed<< s.getSWinRate() << std::setw(7) << std::right << s.getSGoal();
	ostr << std::setw(11) << std::right << s.getSPenalty() << std::endl;
	return ostr;
}
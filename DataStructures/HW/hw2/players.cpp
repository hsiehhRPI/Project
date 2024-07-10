#include <string>
#include <vector>
#include <iostream>
#include "players.h"
#include <iomanip>
//Default constructor
Players::Players(std::string n, std::string t) {
	name = n;
	uni = t;
	goals = 0;
	assists = 0;
	penalties = 0;
}
//Accessor functions
std::string Players::getName() const {
	return name;
}
std::string Players::getUni() const {
	return uni;
}
int Players::getGoal() const {
	return goals;
}
int Players::getAssist() const {
	return assists;
}
int Players::getPenal() const {
	return penalties;
}
//Modifier functions
void Players::set_goal(int g) {
	goals = g;
}
void Players::set_assist(int a) {
	assists = a;
}
void Players::set_penal(int p) {
	penalties = p;
}
//Non-member functions
bool isInFront(const Players& p1, const Players& p2) {
	if (p1.getAssist()+p1.getGoal() > p2.getAssist()+p2.getGoal()) {
		return true;
	}
	else if (p1.getAssist()+p1.getGoal() < p2.getAssist()+p2.getGoal()) {
		return false;
	}
	else {
		if (p1.getPenal() < p2.getPenal()) {
			return true;
		}
		else if (p1.getPenal() > p2.getPenal()) {
			return false;
		}
		else {
			if (p1.getName() < p2.getName()) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& ostr, const Players &p) {
	ostr << std::setw(23) << std::left << p.getName() << std::setw(15) << std::left << p.getUni();
	ostr << std::setw(5) << std::right << p.getGoal() << std::setw(9) << std::right << p.getAssist();
	ostr << std::setw(11) << std::right << p.getPenal() << std::endl;
	return ostr; 	
}
#include <cmath>
#include <iostream>

#include "penalties.h"

Penalties::Penalties(std::string& t) {
	team = t;
	penPercent = 0;
	totalPen = 0;
	totalPenH = 0;
	totalPenM = 0;
	teamPH = 0;
	teamPM = 0;
}

std::string Penalties::getT() const {
	return team;
}
float Penalties::getPenPercent() const {
	return penPercent;
}
int Penalties::getTotalPen() const {
	return totalPen;
}
int Penalties::getTotalPH() const {
	return totalPenH;
}
int Penalties::getTotalPM() const {
	return totalPenM;
}
int Penalties::getTeamPenal()const {
	return tPenal;
}
int Penalties::getTPenH() const {
	return teamPH;
}
int Penalties::getTPenM() const {
	return teamPM;
}



void Penalties::set_penPercent(float pPen) {
	penPercent = pPen;
}
void Penalties::set_TotalPen(int tPen) {
	totalPen = tPen;
}
void Penalties::set_totalPH(int tPenH){
	totalPenH = tPenH; 
}
void Penalties::set_totalPM(int tPenM) {
	totalPenM = tPenM;
}
void Penalties::set_TeamPenal(int tp) {
	tPenal = tp;
}
void Penalties::set_TPenH(int tPh) {
	teamPH = tPh;
}
void Penalties::set_TPenM(int tPm) {
	teamPM = tPm;
}

//OTHER FUNCTIONS
std::ostream& operator<<(std::ostream& ostr, const Penalties& pen){
	ostr<<std::setw(10 + 3);
	ostr<<std::left <<pen.getT();
	ostr<<std::setw(7);
	ostr << std::fixed<<std::right << std::setprecision(2) << pen.getTPenH() <<"h ";
	ostr<<std::setw(2);
	ostr<<std::setprecision(2) << pen.getTPenM() <<"m" << std::endl;
	return ostr;
}

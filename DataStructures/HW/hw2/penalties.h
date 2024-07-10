#ifndef __penalties_h
#define __penalties_h
#include <iostream>
#include <iomanip>

//The penalty class, keeps track of total penalty time(hour & minutes) percent each team contributes, 
//team penalty (hour&minutes) 
class Penalties {
public:
	//CONSTRUCTOR
	Penalties(std::string& tName);

	//ACCESSORS
	std::string getT() const;
	float getPenPercent() const;
	int getTotalPen() const;
	int getTotalPH() const;
	int getTotalPM() const;
	int getTeamPenal()const;
	int getTPenH() const;
	int getTPenM() const;
	//MODIFIERS
	void set_penPercent(float pPen);
	void set_TotalPen(int tPen);
	void set_totalPH(int tPenH);
	void set_totalPM(int tPenM);
	void set_TeamPenal(int tp);
	void set_TPenH(int tPh);
	void set_TPenM(int tPm);

	//OTHER FUNCTIONS

private:
	std::string team;
	float penPercent;
	int totalPen;
	int totalPenH;
	int totalPenM;
	int tPenal;
	int teamPH;
	int teamPM;

};
//Nonmember function
std::ostream& operator<<(std::ostream& ostr, const Penalties& pen);
#endif
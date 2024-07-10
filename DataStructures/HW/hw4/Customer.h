#ifndef __Customer_h_
#define __Customer_h_
#include <iostream>
#include <string>
//This is the class that keeps track of customers
class Customer {
public:
	//CONSTRUCTOR
	Customer(std::string cID_, std::string stat_, int q_, std::string tID_, std::string cName_);
	//ACCESSORS
	std::string cGetCID() const {return cID;}
	std::string cGetStat() const {return status;}
	int cGetQuant() const {return quant;}
	int cGetFixQ() const {return fixQuant;}
	std::string cGetTID() const {return tID;}
	std::string cGetName() const {return cName;}
	int cGetnEvent() const {return nEvents;}
	//MODIFIER
	void cSetState (std::string state) {status = state;}
	void cSetQuan (int s) {quant = s;}
	void cSetnEvent(int e) {nEvents = e;}

private:
	std::string cID, status,tID, cName;
	int quant, fixQuant; 
	int nEvents;
};
std::ostream& operator<<(std::ostream& ostr, const Customer &c);
#endif
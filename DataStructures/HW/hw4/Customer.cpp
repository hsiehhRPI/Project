#include <iostream>
#include <string>
#include "Customer.h"

//CONSTRUCTOR
Customer::Customer(std::string cID_, std::string stat_, int q_, std::string tID_, std::string cName_) {
	cID = cID_;
	status = stat_;
	quant = q_;
	tID = tID_;
	cName = cName_;
	fixQuant = q_;
	nEvents = 0;
}
std::ostream& operator<<(std::ostream& ostr, const Customer &c) {
	ostr << c.cGetCID() << " "<<c.cGetName()<<std::endl;
	if (c.cGetStat() == "rent"){
		ostr << "Rental" << ": "<<c.cGetTID()<< "("<<c.cGetQuant()<<")"<<std::endl;
		ostr<<std::endl;
	}
	else if (c.cGetStat() == "pending") {
		ostr << "Pending" << ": "<<c.cGetTID()<< "("<<c.cGetQuant()<<")"<<std::endl;
		ostr<<std::endl;
	}
	
	return ostr; 
}



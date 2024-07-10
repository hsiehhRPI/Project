#include <iostream>
#include <iomanip>
#include <string>

#include "Tool.h"
Tool::Tool(std::string td_, int tQ, std::string tn) {
	toolID = td_;
	tName = tn;
	tQuan = tQ;
	fixQuan = tQ;
}

std::ostream& operator<<(std::ostream& ostr, const Tool &t) {
	ostr << t.tGetID() << " " << t.tGetQuan()<< " available " << t.tGetTName() << std::endl;
	//I tried to write a << that could output customer information
	//The line of thought lies in that I create different lists that hold 
	//The customer id, name, quantity because we could not access customer class 
	//member functions and has iterators that helps output the information.
	//However, it doesn't actually work
	/*ostr<< "Rental Customers: ";
	t.tGetc_it() = t.tGetRCID().begin();
	t.tGetn_it() = t.tGetCN().begin();
	t.tGetq_it() = t.tGetrQuan().begin();
	for (t.tGetc_it() = t.tGetRCID().begin(); t.tGetc_it() != t.tGetRCID().end(); ++t.tGetRCID()) {
		ostr << *t.tGetc_it() <<" "<<*t.tGetn_it() <<" (" <<*t.tGetq_it() <<")"<<std::endl;
		++t.tGetc_it();
		++t.tGetn_it();
		++t.tGetq_it();
	}
	*/
	return ostr;
}

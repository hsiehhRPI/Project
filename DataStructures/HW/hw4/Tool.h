#ifndef __Tool_h_
#define __Tool_h_
#include <iostream>
#include <string>
#include <list>

class Tool {
public:
	//CONSTRUCTOR
	Tool(std::string td_, int tQ, std::string tn);
	//ACCESSORS
	int tGetQuan() const {return tQuan;}
	std::string tGetID() const {return toolID;}
	std::string tGetTName() const {return tName;}
	int tGetFlex() const {return fixQuan;}
	std::list<std::string>::iterator tGetc_it() {return c_it;}
	std::list<int>::iterator tGetq_it(){return q_it;}
	std::list<std::string>::iterator tGetn_it(){return n_it;}
	std::list<std::string> tGetRCID() const {return rcID;}
	std::list<std::string> tGetPCID() const {return pcID;}
	std::list<std::string> tGetCN() const{return cName;}
	std::list<std::string> tGetPN() const{return pName;}
	std::list<int> tGetrQuan() const{return rQuan;}
	std::list<int> tGetpQuan() const{return pQuan;}

	//MODIFIER
	void tSet_quan(int s) {tQuan = s;}
	void tAdd_rcid(std::string rcid_) {rcID.push_back(rcid_);}
	void tAdd_pcid(std::string pcid_) {pcID.push_back(pcid_);}
	void tAdd_cName(std::string c) {cName.push_back(c);}
	void tAdd_pName(std::string p) {pName.push_back(p);}
	void tAdd_rq(int rq) {rQuan.push_back(rq);}
	void tAdd_pq(int pq) {pQuan.push_back(pq);}



private:
std::string toolID, tName;
int tQuan, fixQuan;
std::list<std::string> rcID;
std::list<std::string> pcID;
std::list<std::string> cName;
std::list<std::string> pName;
std::list<int> rQuan;
std::list<int> pQuan;
std::list<int>::iterator q_it;
std::list<std::string>::iterator c_it;
std::list<std::string>::iterator n_it;
};
std::ostream& operator<<(std::ostream& ostr, const Tool &t);
#endif
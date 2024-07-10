#ifndef __Fighter_h_
#define __Fighter_h_

#include <string>
#include <iostream>

/* This class create different Super Smash Bros character as fighter class objects.
   The fighter class contain the moves each fighers can do and the speed of the frame for their moves

*/
class Fighter {
public:
	//CONSTRUCTOR
	//There are no default constructors because we need the name of the fighter
	Fighter(){}	//This line had to be added else there is going to be compilation error
	Fighter(std::string name_, std::string jab_, std::string fTilt_, std::string uTilt_, std::string dTilt_, std::string fSmash_, std::string uSmash_, std::string dSmash_);

	//ACCESSOR
	std::string getFName() const {return name;}
	std::string getJab() const {return jab;}
	std::string getFTilt() const {return fTilt;}
	std::string getUTilt() const {return uTilt;}
	std::string getDTilt() const {return dTilt;}
	std::string getFSmash() const {return fSmash;}
	std::string getUSmash() const {return uSmash;}
	std::string getDSmash() const {return dSmash;}

	//MODIFIER
	void set_jab (std::string j) {jab = j;}
	void set_fTilt (std::string ft) {fTilt = ft;}
	void set_uTilt (std::string ut) {uTilt = ut;}
	void set_dTilt (std::string dt) {dTilt = dt;}
	void set_fSmash (std::string fs) {fSmash = fs;}
	void set_uSmash (std::string us) {uSmash = us;}
	void set_dSmash (std::string ds) {dSmash = ds;}

private:
	std::string name, jab, fTilt, uTilt, dTilt, fSmash, uSmash, dSmash;
};
#endif
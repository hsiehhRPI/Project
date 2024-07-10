#include <string>
#include <iostream>
#include "Fighter.h"

//CONSTRUCTOR and how it assigned the input value to private member
Fighter::Fighter(std::string name_, std::string jab_, std::string fTilt_, std::string uTilt_, std::string dTilt_, std::string fSmash_, std::string uSmash_, std::string dSmash_) {
	name = name_;
	jab = jab_;
	fTilt = fTilt_;
	uTilt = uTilt_;
	dTilt = dTilt_;
	fSmash = fSmash_;
	uSmash = uSmash_;
	dSmash = dSmash_; 
}


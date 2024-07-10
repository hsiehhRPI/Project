NOTE: CURRENT COMPILER ERRORS
1st compile: 
	Compiling all the files together:
	- Some warning for unused variable and multiple declaration of the same function, and a string fo words reguarding ostr, otherwise compiles
	point.cpp:
	- Unused variable "answer"
	- Undefined reference to main
	- ld returned 1 exit status
	point (1).cpp:
	- Unused variable "answer"
	- Undefined reference to main
	- ld returned 1 exit status
	road.cpp:
	- sort is not member of std
	- 
	

THIS FILE CONTAIN NOTE OF THE EDITS I HAD MADE TO EACH FILE:
line.h
roads.cpp
point.h
	- Added the ifndef guard
	- Change the curly brackets in the constructor definition to surround the three input variables and added a semicolon at the end
point (1).cpp
	- Changed the name of the file to point_1.cpp(otherwise step4 cannot be executed)
	- Line 8 - 11, added missing semicolons

point.cpp
	- In the operator<< function, added the missing semicolons at the end of each line
	- In compute slope function, changed return rise/run to return answer since the variable "answer" is already assigned rise/run

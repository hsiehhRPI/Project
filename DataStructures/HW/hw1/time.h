// FILE: time.h
// Header file the Time class
class Time {
public:
	//CONSTRUCTORS
	Time();
	Time(int ahour, int aminute, int asecond);
	
	//ACCESSORS
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	
private:
	int hour;
	int minute;
	int second;
};
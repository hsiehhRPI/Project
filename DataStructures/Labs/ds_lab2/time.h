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

	//MODIFIER
	void setHour(int ahour);
	void setMinute(int aminute);
	void setSecond(int asecond);
	void PrintAMPM();

private:
	int hour;
	int minute;
	int second;
};

//non-member function
//Prototype
bool IsEarlierThan(const Time& t1, const Time& t2);
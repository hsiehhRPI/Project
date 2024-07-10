//FILE: date.cpp
//Impeliment the functions in time.h
#include <iostream>
#include "Time.h"

//Default constructor
Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int ahour, int aminute, int asecond) {
	hour = ahour;
	minute = aminute;
	second = asecond;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int h) {
	hour = h;
}

void Time::setMinute(int m) {
	minute = m;
}

void Time::setSecond(int s) {
	second = s;
}

void Time::PrintAMPM() {
	if (hour == 0) {
		hour += 12;
		if (minute < 10 && second < 10) {
			std::cout << hour << ":0" << minute << ":0" << second <<" AM"<< std::endl;
		}
		else if (minute > 10 && second < 10) {
			std::cout << hour << ":" << minute << ":0" << second <<" AM"<< std::endl;

		}
		else if (minute < 10 && second > 10) {
			std::cout << hour << ":0" << minute << ":" << second <<" AM"<< std::endl;
		}
		else{
			std::cout << hour << ":" << minute << ":" << second <<" AM"<< std::endl;
		}
	}
	else if (hour > 12) {
		hour -= 12;
		if (minute < 10 && second < 10) {
			std::cout << hour << ":0" << minute << ":0" << second <<" PM"<< std::endl;
		}
		else if (minute > 10 && second < 10) {
			std::cout << hour << ":" << minute << ":0" << second <<" PM"<< std::endl;

		}
		else if (minute < 10 && second > 10) {
			std::cout << hour << ":0" << minute << ":" << second <<" PM"<< std::endl;
		}
		else{
			std::cout << hour << ":" << minute << ":" << second <<" PM"<< std::endl;
		}
	}
	else if (hour < 12 && hour > 0){
		if (minute < 10 && second < 10) {
			std::cout << hour << ":0" << minute << ":0" << second <<" AM"<<std::endl;
		}
		else if (minute > 10 && second < 10) {
			std::cout << hour << ":" << minute << ":0" << second <<" AM"<<std::endl;

		}
		else if (minute < 10 && second > 10) {
			std::cout << hour << ":0" << minute << ":" << second <<" AM"<<std::endl;
		}
		else{
			std::cout << hour << ":" << minute << ":" << second <<" AM"<<std::endl;
		}
	}
	else {
		if (minute < 10 && second < 10) {
			std::cout << hour << ":0" << minute << ":0" << second <<" PM"<<std::endl;
		}
		else if (minute > 10 && second < 10) {
			std::cout << hour << ":" << minute << ":0" << second <<" PM"<<std::endl;

		}
		else if (minute < 10 && second > 10) {
			std::cout << hour << ":0" << minute << ":" << second <<" PM"<<std::endl;
		}
		else{
			std::cout << hour << ":" << minute << ":" << second <<" PM"<<std::endl;
		}
	}
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour() > t2.getHour()) {
		return false;
	} else if (t1.getHour() < t2.getHour()) {
		return true;
	} else {
		if (t1.getMinute() > t2.getMinute()) {
			return false;
		}
		else if (t1.getMinute() < t2.getMinute()) {
			return true;
		}
		else {
			if (t1.getSecond() > t2.getSecond()) {
				return false;
			}
			else if (t1.getSecond() < t2.getSecond()) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
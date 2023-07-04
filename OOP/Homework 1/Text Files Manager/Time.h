#pragma once
#include "Date.h"

//help form Angel Dimitriev gitHub
class Time 
{
	unsigned hours;
	unsigned mins;
	unsigned seconds;
	Date date;

	bool isInInterval(unsigned upperInterval, unsigned value);
public:
	Time();
	Time(unsigned hours, unsigned mins, unsigned seconds);
	Time(unsigned seconds);
	Time(int year, int month, int day, int hour, int minute, int second);

	void setHours(unsigned hours);
	void setMins(unsigned mins);
	void setSeconds(unsigned seconds);

	unsigned getHours() const;
	unsigned getMins() const;
	unsigned getSeconds() const;
	
	bool compareTime(const Time& t1) const;

	void print() const;
};
#include <iostream>
#include <iomanip>
#include "Time.h"
#include "helpers.h"

bool Time::isInInterval(unsigned upperInterval, unsigned value)
{
	return value <= upperInterval;
}

Time::Time(unsigned hours, unsigned mins, unsigned seconds)
{
	setHours(hours);
	setMins(mins);
	setSeconds(seconds);	
}

Time::Time(int year, int month, int day, int hour, int minute, int second) : 
	date(day, month,year), hours(hour), mins(minute), seconds(second) {}

Time::Time():hours(0),mins(0),seconds(0){}

Time::Time(unsigned seconds)
{
	if (!isInInterval(24 * 3600, seconds))
		seconds = 0;

	setHours(seconds / 3600);
	seconds %= 3600;

	setMins(seconds / 60);
	seconds %= 60;

	setSeconds(seconds);
}

void Time::setHours(unsigned hours)
{
	if (isInInterval(23, hours))
		this->hours = hours;
	else
		this->hours = 0;
}

void Time::setMins(unsigned mins)
{
	if (isInInterval(59, mins))
		this->mins = mins;
	else
		this->mins = 0;
}

void Time::setSeconds(unsigned seconds)
{
	if (isInInterval(59, seconds))
		this->seconds = seconds;
	else
		this->seconds = 0;
}

unsigned Time::getHours() const
{
	return hours;
}

unsigned Time::getMins() const
{
	return mins;
}

unsigned Time::getSeconds() const
{
	return seconds;
}

void Time::print() const
{
	std::cout << ((hours < 10) ? "0" : "") << hours << " : "
		<< ((mins < 10) ? "0" : "") << mins << " : "
		<< ((seconds < 10) ? "0" : "") << seconds << std::endl;
	date.print();
}


bool Time::compareTime(const Time& t1) const
{
	int seconds1 = t1.hours * 3600 + t1.mins * 60 + t1.seconds;
	int seconds2 = this->hours * 3600 + this->mins * 60 + this->seconds;
	return seconds2 > seconds1;
}
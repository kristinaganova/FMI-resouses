#pragma once

//help form Angel Dimitrievs gitHub
class Date
{
	unsigned day;
	unsigned month;
	unsigned year;
public:
	Date();
	Date(unsigned day, unsigned month, unsigned year);

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	bool isLeapYear(int year) const;
	bool isValidDay(int day) const;

	void print() const;
};
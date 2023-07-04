#include <iostream>
#include "Date.h"
#include "constants.h"
#include "helpers.h"
#include <iomanip>

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

Date::Date() : day(0), month(0), year(0) {}

void Date::setDay(unsigned day)
{
	if (isValidDay(day))
		this->day = day;
	else
		this->day = 0;
}

void Date::setMonth(unsigned month)
{
	if (month > 0 && month <= MAX_MONTHS)
		this->month = month;
	else
		this->month = 1;
}

void Date::setYear(unsigned year)
{
	if (year < 0)
	{
		this->year = 0;
	}
	else {
		this->year = year;
	}
}

unsigned Date::getDay() const
{
	return day;
}

unsigned Date::getMonth() const
{
	return month;
}

unsigned Date::getYear() const
{
	return year;
}

void Date::print() const
{
	std::cout << ((day < 10) ? "0" : "") << day << " . " << ((month < 10) ? "0" : "") << month << " . " << year;
}

bool Date::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool Date::isValidDay(int day) const
{
	if (day < 1)
	{
		return false;
	}

	int daysInMonth;
	switch (month) {
	case 2:
		daysInMonth = isLeapYear(year) ? 29 : 28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		daysInMonth = 30;
		break;
	default:
		daysInMonth = 31;
	}

	return day <= daysInMonth;
}
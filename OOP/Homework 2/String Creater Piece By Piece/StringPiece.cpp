#include "StringPiece.h"
#include <iostream>
#pragma warning (disable : 4996)

namespace 
{
	static const size_t MAX_DIGITS = 16;

	void mySwap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}

	void convertNumberToString(size_t num, char* str, size_t& len)
	{
		len = 0;
		size_t n = num;

		if (n == 0)
		{
			str[len++] = '0';
		}
		else
		{
			while (n > 0)
			{
				str[len++] = '0' + (n % 10);
				n /= 10;
			}
		}

		for (size_t i = 0; i < len / 2; ++i)
		{
			mySwap(str[i], str[len - i - 1]);
		}
	}
}

StringPiece::StringPiece()
	: _begin(nullptr), _end(nullptr) {}

StringPiece::StringPiece(const char* begin, const char* end)
	: _begin(begin), _end(end) {}

StringPiece::StringPiece(const char* str)
	: _begin(str), _end(str + strlen(str)) {}

const char* StringPiece::c_str() const
{
	if (_begin == nullptr)
	{
		return "";
	}
	size_t len = length();
	char* str = new char[len + 1];
	strcpy(str, _begin);
	str[len] = '\0';
	return str;
}

const char* StringPiece::get() const
{
	return _begin;
}

void StringPiece::set(const char* str)
{
	_begin = str;
	_end = str + strlen(str);
}

size_t StringPiece::length() const
{
	return _end - _begin;
}

void StringPiece::append(const char* str, size_t len)
{
	size_t oldLen = length();
	char* newStr = new char[oldLen + len];

	for (size_t i = 0; i < oldLen; ++i) 
	{
		newStr[i] = _begin[i];
	}
	for (size_t i = 0; i < len; ++i) 
	{
		newStr[i + oldLen] = str[i];
	}

	_begin = newStr;
	_end = newStr + oldLen + len;
}

void StringPiece::appendInTheBeggining(const char* str, size_t len)
{
	size_t oldLen = length();
	char* newStr = new char[oldLen + len];

	for (size_t i = 0; i < len; i++) 
	{
		newStr[i] = str[i];
	}
	for (size_t i = 0; i < oldLen; i++)
	{
		newStr[len + i] = _begin[i];
	}

	_begin = newStr;
	_end = newStr + oldLen + len;
}

void StringPiece::print() const
{
	size_t len = length();
	for (const char* p = _begin; p < _end; p++)
	{
		std::cout << (*p);
	}
	std::cout << std::endl;
}

const char* StringPiece::toString() const
{
	return c_str();
}

StringPiece& StringPiece::operator<<(const char* str)
{
	if (strlen(str) + length() > MAX_PIECE_LEN)
	{
		throw std::out_of_range("Maximum reached");
	}
	append(str, strlen(str));
	return *this;
}

StringPiece& StringPiece::operator<<(size_t num)
{
	char str[MAX_DIGITS];
	size_t len = 0;

	convertNumberToString(num, str, len);

	if (len + length() > MAX_PIECE_LEN)
	{
		throw std::out_of_range("Maximum reached");
	}
	append(str, len);

	return *this;
}

StringPiece& StringPiece::operator>>(const char* str)
{
	if (strlen(str) + length() > MAX_PIECE_LEN)
	{
		throw std::out_of_range("Maximum reached");
	}
	appendInTheBeggining(str, strlen(str));
	return *this;
}

StringPiece& StringPiece::operator>>(size_t num)
{
	char str[MAX_DIGITS];
	size_t len = 0;

	convertNumberToString(num, str, len);
	if (len + length() > MAX_PIECE_LEN)
	{
		throw std::out_of_range("Maximum reached");
	}
	appendInTheBeggining(str, len);
	return *this;
}

void StringPiece::removeFirstKChars(size_t k)
{
	_begin += k;
}

void StringPiece::removeLastKChars(size_t k)
{
	_end -= k;
}

void StringPiece::changeCharByIndex(int index, char c)
{
	if (index >= 0 && index < length())
	{
		char* p = (char*)_begin + index;
		*p = c;
	}
}
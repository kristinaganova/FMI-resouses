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

	void convertNumberToString(size_t num, char* str, unsigned int& len)
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
    : _start(0), _end(0)
{
    _str[0] = '\0';
}

StringPiece::StringPiece(const char* str)
    : _start(0), _end(strlen(str))
{
    strncpy(_str, str, MAX_PIECE_LEN);
    _str[MAX_PIECE_LEN] = '\0';
}

StringPiece::StringPiece(const char* str, unsigned int start, unsigned int end)
    : _start(start), _end(end)
{
    strncpy(_str, str + start, end - start);
    _str[end - start] = '\0';
}

const char* StringPiece::c_str() const
{
    return _str;
}

const char* StringPiece::get() const
{
    return _str;
}

void StringPiece::set(const char* str)
{
    strncpy(_str, str, MAX_PIECE_LEN);
    _str[MAX_PIECE_LEN] = '\0';
    _start = 0;
    _end = strlen(str);
}

size_t StringPiece::length() const
{
    return _end - _start;
}

void StringPiece::append(const char* str, unsigned int len)
{
    unsigned int oldLen = length();
    unsigned int newLen = oldLen + len;
    if (newLen > MAX_PIECE_LEN)
    {
        throw std::out_of_range("Maximum reached");
    }

    strncpy(_str + oldLen, str, len);
    _str[newLen] = '\0';
    _end = _start + newLen;
}

void StringPiece::appendInTheBeginning(const char* str, unsigned int len)
{
    unsigned int oldLen = length();
    unsigned int newLen = oldLen + len;
    if (newLen > MAX_PIECE_LEN)
    {
        throw std::out_of_range("Maximum reached");
    }

    for (unsigned int i = oldLen; i > 0; --i)
    {
        _str[_start + i + len - 1] = _str[_start + i - 1];
    }

    for (unsigned int i = 0; i < len; ++i)
    {
        _str[_start + i] = str[i];
    }

    _start -= len;
    _end = _start + newLen;
}


void StringPiece::print() const
{
    std::cout << _str << std::endl;
}

const char* StringPiece::toString() const
{
    return _str;
}

StringPiece& StringPiece::operator<<(const char* str)
{
    append(str, strlen(str));
    return *this;
}

StringPiece& StringPiece::operator<<(unsigned int num)
{
    char numStr[MAX_PIECE_LEN];
    unsigned int len = 0;

    convertNumberToString(num, numStr, len);

    append(numStr, len);
    return *this;
}

StringPiece& StringPiece::operator>>(const char* str)
{
    unsigned int len = strlen(str);
    appendInTheBeginning(str, len);
    return *this;
}

StringPiece& StringPiece::operator>>(unsigned int num)
{
    char numStr[MAX_PIECE_LEN];
    unsigned int len = 0;

    convertNumberToString(num, numStr, len);
    appendInTheBeginning(numStr, len);
    return *this;
}

void StringPiece::removeFirstKChars(unsigned int k)
{
    if (k >= length())
    {
        _start = _end;
        _str[0] = '\0';
    }
    else
    {
        _start += k;
        strncpy(_str, _str + k, MAX_PIECE_LEN - k);
        _str[MAX_PIECE_LEN - k] = '\0';
    }
}

void StringPiece::removeLastKChars(unsigned int k)
{
    if (k >= length())
    {
        _end = _start;
        _str[0] = '\0';
    }
    else
    {
        _end -= k;
        _str[_end - _start] = '\0';
    }
}

void StringPiece::changeCharByIndex(int index, char c)
{
    if (index >= 0 && index < length())
    {
        _str[_start + index] = c;
    }
}

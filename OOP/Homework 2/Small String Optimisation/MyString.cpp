#include "MyString.h"
#include <cstring>
#pragma warning (disable:4996)

MyString::MyString(size_t capacity) : _length(capacity - 1), _isOnHeap(MyString::isOnHeap(capacity))
{
    if (MyString::_isOnHeap) 
    {
        sso._heap = new char[capacity];
    }
}

void MyString::copyFrom(const MyString& other)
{
    _length = other._length;
    _isOnHeap = other._isOnHeap;
    if (_isOnHeap)
    {
        sso._heap = new char[_length + 1];
        std::strcpy(sso._heap, other.sso._heap);
    }
    else
    {
        std::strcpy(sso._stack, other.sso._stack);
    }
}

void MyString::free()
{
    if (_isOnHeap)
    {
        delete[] sso._heap;
    }
    _length = 0;
}

void MyString::move(MyString&& other)
{
    _isOnHeap = other._isOnHeap;
    _length = other._length;

    if (_isOnHeap) 
    {
        sso._heap = other.sso._heap;
        other.sso._heap = nullptr;
    }
    else 
    {
        for (int i = 0; i < SSO_SIZE + 1; i++)
        {
            sso._stack[i] = other.sso._stack[i];
        }
    }
}

bool MyString::isOnHeap(size_t length)
{
    return length > (SSO_SIZE - 1);
}

MyString::MyString() : _length(0), _isOnHeap(false)
{
    sso._stack[0] = '\0';
}

MyString::MyString(const char* data) : _length(std::strlen(data)), _isOnHeap(MyString::isOnHeap(_length))
{
    if (_isOnHeap)
    {
        sso._heap = new char[_length + 1];
        std::strcpy(sso._heap, data);
    }
    else
    {
        std::strcpy(sso._stack, data);
    }
}

MyString::MyString(const MyString& other) : _length(other._length), _isOnHeap(other._isOnHeap)
{
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}


MyString::~MyString()
{
    free();
}

MyString::MyString(MyString&& other) noexcept
{
    move(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other)
    {
        free();
        move(std::move(other));
    }

    return *this;
}

size_t MyString::length() const
{
    return _length;
}

MyString& MyString::operator+=(const MyString& other)
{
    size_t new_length = _length + other._length;
    bool new_is_on_heap = MyString::isOnHeap(new_length);
    char* new_data;

    if (new_is_on_heap)
    {
        new_data = new char[new_length + 1];
        std::strcpy(new_data, _isOnHeap ? sso._heap : sso._stack);
        std::strcpy(new_data + _length, other._isOnHeap ? other.sso._heap : other.sso._stack);
    }
    else
    {
        new_data = sso._stack;
        std::strcpy(new_data + _length, other._isOnHeap ? other.sso._heap : other.sso._stack);
    }

    if (_isOnHeap)
    {
        delete[] sso._heap;
    }

    MyString::_isOnHeap = new_is_on_heap;
    if (_isOnHeap)
    {
        sso._heap = new_data;
    }
    _length = new_length;

    return *this;
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
    if (begin >= length())
    {
        return MyString();
    }

    if (begin + howMany > length())
    {
        howMany = length() - begin;
    }

    MyString result;
    result._length = howMany;

    if (MyString::isOnHeap(howMany))
    {
        result.sso._heap = new char[howMany + 1];
        result._isOnHeap = true;
    }
    else
    {
        result._isOnHeap = false;
    }

    for (size_t i = 0; i < howMany; ++i)
    {
        result[i] = (*this)[begin + i];
    }

    result[howMany] = '\0';
    return result;
}

char& MyString::operator[](size_t index)
{
    return _isOnHeap ? sso._heap[index] : sso._stack[index];
}

char MyString::operator[](size_t index) const
{
    return _isOnHeap ? sso._heap[index] : sso._stack[index];
}

const char* MyString::c_str() const
{
    return MyString::_isOnHeap ? sso._heap : sso._stack;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs);
    result += rhs;
    return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
    char buff[1024];
    is >> buff; 

    str.free();

    str._length = strlen(buff);

    if (MyString::isOnHeap(str._length))
    {
        str._isOnHeap = true;
        str.sso._heap = new char[str._length + 1];
        strcpy(str.sso._heap, buff);
    }
    else
    {
        str._isOnHeap = false;
        strcpy(str.sso._stack, buff);
    }

    return is;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
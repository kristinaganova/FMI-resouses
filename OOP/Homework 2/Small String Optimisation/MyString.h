#pragma once
#include <iostream>

const short SSO_SIZE = 15; 

union StackHeapUnion
{
    char _stack[SSO_SIZE + 1];
    char* _heap;
};

class MyString
{
private:
    StackHeapUnion sso;
    size_t _length;
    bool _isOnHeap;
public:
    MyString();
    MyString(const char* data);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    size_t length() const;
    MyString& operator+=(const MyString& other);

    MyString substr(size_t begin, size_t howMany) const;

    char& operator[](size_t index);
    char operator[](size_t index) const;

    const char* c_str() const;

    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend std::istream& operator>>(std::istream&, MyString& str);

private:
    static bool isOnHeap(size_t length);
    explicit MyString(size_t capacity);

    void copyFrom(const MyString& data);
    void free();
    void move(MyString&& other);
};

MyString operator+(const MyString& lhs, const MyString& rhs);

std::ostream& operator<<(std::ostream& os, const MyString& str);

std::istream& operator>>(std::istream& os, MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
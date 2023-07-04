#include <iostream>
#include <cassert>
#include "MyString.h"

int main() 
{
    char cstr[] = "hello";
    MyString str1(cstr);
    assert(str1.length() == 5);
    assert(str1[0] == 'h');
    assert(str1[4] == 'o');

    MyString str2(str1);
    assert(str2.length() == 5);
    assert(str2[0] == 'h');
    assert(str2[4] == 'o');

    MyString str3 = "world";
    assert(str3.length() == 5);
    assert(str3[0] == 'w');
    assert(str3[4] == 'd');

    str3 = str1;
    assert(str3.length() == 5);
    assert(str3[0] == 'h');
    assert(str3[4] == 'o');

    str3 += "!";
    assert(str3.length() == 6);
    assert(str3[5] == '!');

    MyString str4 = str1 + " " + str3;
    assert(str4.length() == 12);
    assert(str4[0] == 'h');
    assert(str4[4] == 'o');
    assert(str4[5] == ' ');
    assert(str4[6] == 'h');
    assert(str4[11] == '!');

    assert(str1 == "hello");
    assert(str1 != "world");
    assert(str1 < "jello");
    assert(str1 <= "hello");
    assert(str1 > "cello");
    assert(str1 >= "hello");

    MyString substr = str1.substr(1, 3);
    assert(substr.length() == 3);
    assert(substr[0] == 'e');
    assert(substr[2] == 'l'); 

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

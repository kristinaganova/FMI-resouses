#include <fstream>
#include "Set.h"
#include "MyString.h"
#include <string>
#include "UnionSet.h"
#include "IntersectionSet.h"
#include "CriterionSet.hpp"

MyString readString(std::ifstream& file);

bool containsNumber(const Vector<uint32_t>& numbers, size_t number);

bool isDivisibleByOne(const Vector<uint32_t>& numbers, size_t number);

bool criterionOne(const Vector<uint32_t>& numbers, size_t number);

bool criterionTwo(const Vector<uint32_t>& numbers, size_t number);

bool criterionThree(const Vector<uint32_t>& numbers, size_t number);

Set* constructSetFromFile(std::ifstream& file);

void run();
#include "Set.h"
#include <iostream>

static const unsigned char BITS[] = { 128, 64, 32, 16, 8, 4, 2, 1 };
static const unsigned char MAX_BITS = 8;
static const unsigned char ALL_ONES = 255;
static const short MAX_ALLOWED_NUMBER = 1000;

Set::Set() = default;

Set::~Set() = default;

const Vector<unsigned char>& Set::getNumbers() const
{
	{ return numbers; }
}

void Set::setBit(size_t index)
{
	numbers[index / MAX_BITS] |= (1 << (index % MAX_BITS));
}

void Set::clearBit(size_t index)
{
	numbers[index / MAX_BITS] &= ~(1 << (index % MAX_BITS));
}

bool Set::isBitSet(size_t index) const
{
	return (numbers[index / MAX_BITS] & (1 << (index % MAX_BITS))) != 0;
}

void Set::addNumber(size_t number)
{
	if (number / MAX_BITS >= numbers.getSize())
	{
		resize(number / MAX_BITS + 1);
	}

	setBit(number);
}

void Set::removeNumber(size_t number)
{
	if (number / MAX_BITS >= numbers.getSize())
	{
		return;
	}

	clearBit(number);
}

void Set::printBits() const
{
	for (size_t i = 0; i < numbers.getSize(); i++)
	{
		for (size_t j = 0; j < MAX_BITS; j++)
		{
			std::cout << isBitSet(i * MAX_BITS + j);
		}
	}
}

void Set::resize(size_t newCapacity)
{
	Vector<unsigned char> newNumbers(newCapacity);
	for (size_t i = 0; i < numbers.getSize(); i++)
	{
		newNumbers[i] = numbers[i];
	}
	numbers = std::move(newNumbers);
}
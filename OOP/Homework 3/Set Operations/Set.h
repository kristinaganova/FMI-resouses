#pragma once
#include "Vector.hpp"

#pragma once
#include "Vector.hpp"

class Set
{
protected:
	Vector<unsigned char> numbers;

	void setBit(size_t index);
	void clearBit(size_t index);
	bool isBitSet(size_t index) const;

public:
	Set();
	virtual ~Set();

	const Vector<unsigned char>& getNumbers() const;

	void addNumber(size_t number);
	void removeNumber(size_t number);

	virtual bool contains(size_t number) const = 0;
	virtual const Set& merge(const Set& other) const = 0;
	virtual const Set& intersect(const Set& other) const = 0;

	virtual void print() const = 0;
	void printBits() const;

private:
	void resize(size_t newCapacity);
};
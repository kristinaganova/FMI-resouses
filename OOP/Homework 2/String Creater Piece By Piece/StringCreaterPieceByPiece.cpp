#include "StringCreaterPieceByPiece.h"
#include <iostream>
#pragma warning (disable : 4996)

namespace
{
	const short INITIAL_CAPACITY = 4;
	const short RESIZE_COEF = 2;
	const short SPACES_COUNT = 20;
}

void StringCreaterPieceByPiece::resize(size_t newCapacity)
{
	if (newCapacity <= capacity)
	{
		newCapacity = capacity;
	}

	StringPiece** temp = new StringPiece * [newCapacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = pieces[i];
	}
	delete[] pieces;
	capacity = newCapacity;
	pieces = temp;
}

void StringCreaterPieceByPiece::assertIndex(size_t index) const
{
	if (index >= size)
	{
		throw std::exception("Out of range");
	}
}

void StringCreaterPieceByPiece::upsizeIfNeeded()
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEF);
	}
}

void StringCreaterPieceByPiece::downsizeIfNeeded()
{
	if (size * RESIZE_COEF * RESIZE_COEF <= capacity)
	{
		resize(capacity / RESIZE_COEF);
	}
}

StringCreaterPieceByPiece::StringCreaterPieceByPiece()
	: StringCreaterPieceByPiece(INITIAL_CAPACITY) {}

StringCreaterPieceByPiece::StringCreaterPieceByPiece(size_t capacity)
	: size(0), capacity(capacity)
{
	pieces = new StringPiece * [capacity];
}

StringCreaterPieceByPiece::StringCreaterPieceByPiece(const StringCreaterPieceByPiece& other)
{
	copyfrom(other);
}

StringCreaterPieceByPiece& StringCreaterPieceByPiece::operator=(const StringCreaterPieceByPiece& other)
{
	if (this != &other)
	{
		free();
		copyfrom(other);
	}

	return (*this);
}

StringCreaterPieceByPiece::~StringCreaterPieceByPiece()
{
	free();
}

size_t StringCreaterPieceByPiece::getSize() const
{
	return size;
}

size_t StringCreaterPieceByPiece::getCapacity() const
{
	return capacity;
}

void StringCreaterPieceByPiece::addPiece(const char* str)
{
	upsizeIfNeeded();

	pieces[size] = new StringPiece(str);
	size++;
}

void StringCreaterPieceByPiece::swapPices(size_t inx1, size_t inx2)
{
	assertIndex(inx1);
	assertIndex(inx2);
	StringPiece* temp = pieces[inx1];
	pieces[inx1] = pieces[inx2];
	pieces[inx2] = temp;
}

void StringCreaterPieceByPiece::remove(size_t index)
{
	assertIndex(index);

	delete pieces[index];
	for (size_t i = index; i < size - 1; ++i)
	{
		pieces[i] = pieces[i + 1];
	}
	pieces[size - 1] = nullptr;
	--size;

	downsizeIfNeeded();
}

size_t StringCreaterPieceByPiece::length() const
{
	size_t len = 0;
	for (size_t i = 0; i < size; i++)
	{
		len += pieces[i]->length();
	}
	return len;
}

MyString StringCreaterPieceByPiece::toString() const
{
	char* str = new char[length() + SPACES_COUNT + 1];
	str[0] = '\0'; 
	for (size_t i = 0; i < size - 1; i++) 
	{
		if (pieces[i]->length() == 0) 
		{
			strcat(str, "                    "); 
		}
		else
		{
			strcat(str, pieces[i]->toString()); 
		}
	}
	if (size > 0) 
	{
		strcat(str, pieces[size - 1]->toString()); 
	}

	MyString result(str);
	delete[] str; 
	return result;
}


StringPiece& StringCreaterPieceByPiece::operator[](size_t index)
{
	assertIndex(index);
	return (*pieces[index]);
}

const StringPiece& StringCreaterPieceByPiece::operator[](size_t index) const
{
	assertIndex(index);
	return (*pieces[index]);
}

void StringCreaterPieceByPiece::copyfrom(const StringCreaterPieceByPiece& other)
{
	pieces = new StringPiece * [other.capacity];
	capacity = other.capacity;
	size = other.size;

	for (size_t i = 0; i < size; i++)
	{
		pieces[i] = new StringPiece(*other.pieces[i]);
	}

	if (size < capacity) 
	{
		pieces[size] = nullptr;
	}
}

void StringCreaterPieceByPiece::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete pieces[i];
	}
	delete[] pieces;
	capacity = size = 0;
}
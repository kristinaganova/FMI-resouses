#pragma once
#include<iostream>
#include "StringPiece.h"
#include "MyString.h"

class StringCreaterPieceByPiece
{
	StringPiece** pieces;
	size_t capacity;
	size_t size;

	void resize(size_t newCapacity);
	void assertIndex(size_t index) const;
	void upsizeIfNeeded();
	void downsizeIfNeeded();

public:
	StringCreaterPieceByPiece();
	StringCreaterPieceByPiece(size_t capacity);
	StringCreaterPieceByPiece(const StringCreaterPieceByPiece& other);
	StringCreaterPieceByPiece& operator=(const StringCreaterPieceByPiece& other);
	~StringCreaterPieceByPiece();

	size_t getSize() const;
	size_t getCapacity() const;

	void addPiece(const char* str);
	void swapPices(size_t inx1, size_t inx2);
	void remove(size_t index);
	size_t length() const;

	MyString toString() const;
	StringPiece& operator[](size_t index);
	const StringPiece& operator[](size_t index) const;

private:
	void copyfrom(const StringCreaterPieceByPiece& other);
	void free();
};
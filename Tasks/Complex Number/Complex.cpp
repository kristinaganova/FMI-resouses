#pragma once
#include <iostream>
#include"Complex.h"


int ComplexNumbers::getReal() const
{
	return real;
}

int ComplexNumbers::getImagery() const
{
	return imagery;
}

void ComplexNumbers::setReal(int real)
{
	this->real = real;
}

void ComplexNumbers::setImagery(int imagery)
{
	this->imagery = imagery;
}

ComplexNumbers::ComplexNumbers(int real, int imagery)
{
	setReal(real);
	setImagery(imagery);
}

ComplexNumbers::ComplexNumbers() : ComplexNumbers(0,0) {};

bool ComplexNumbers::isEqual(const ComplexNumbers& num) const
{
	if (num.real == this->real && num.imagery == this->imagery)
	{
		return true;
	}

	return false;
}

ComplexNumbers ComplexNumbers::add(const ComplexNumbers& num) const
{
	ComplexNumbers result;
	result.real = num.real + this->real;
	result.imagery = num.imagery + this->imagery;
	return  result;
}

ComplexNumbers ComplexNumbers::subtract(const ComplexNumbers& num) const
{
	ComplexNumbers result;
	result.real = this->real - num.real;
	result.imagery = this->imagery - num.imagery ;
	return  result;
}

ComplexNumbers ComplexNumbers::multiply(const ComplexNumbers& num) const
{
	ComplexNumbers result;
	result.real = num.real * this->real - num.imagery * this->imagery;
	result.imagery = num.real * this->imagery + num.imagery * this->real;

	return result;
}

ComplexNumbers ComplexNumbers::conjugate() const
{
	ComplexNumbers result;
	result.real = this->real;
	result.imagery = -this->imagery;

	return result;
}

ComplexNumbers ComplexNumbers::getConjugated() const
{
	return this->conjugate();
}

void ComplexNumbers::print() const
{
	std::cout << this->real << " ";
	if (this->imagery > 0)
	{
		std::cout << " + " << this->imagery << "i";
	}
	else if (this->imagery == 0)
	{
		std::cout << " ";
	}
	else
	{
		std::cout << this->imagery << "i";
	}
}


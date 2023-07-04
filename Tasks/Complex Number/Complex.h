#pragma once
class ComplexNumbers 
{
private:

	int real;
	int imagery;

public:

	ComplexNumbers(int real, int imagery);
	ComplexNumbers();

	int getReal() const;
	int getImagery() const;
	void setReal(int real);
	void setImagery(int real);

	bool isEqual(const ComplexNumbers& num) const;
	ComplexNumbers add(const ComplexNumbers& num) const;
	ComplexNumbers subtract(const ComplexNumbers& num) const;
	ComplexNumbers multiply(const ComplexNumbers& num) const;
	ComplexNumbers conjugate() const;
	ComplexNumbers getConjugated() const;

	void print() const;
};
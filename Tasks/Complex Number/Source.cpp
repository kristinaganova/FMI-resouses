#include "Complex.h"

#include <iostream>

int main() {
    ComplexNumbers a(1, 2);
    ComplexNumbers b(6, -5);

    std::cout << "a: ";
    a.print();
    std::cout << std::endl;

    std::cout << "b: ";
    b.print();
    std::cout << std::endl;

    std::cout << "a + b = ";
    a.add(b).print();
    std::cout << std::endl;

    std::cout << "a - b = ";
    a.subtract(b).print();
    std::cout << std::endl;

    std::cout << "a * b = ";
    a.multiply(b).print();
    std::cout << std::endl;

    std::cout << "a conjugated: ";
    a.getConjugated().print();
    std::cout << std::endl;

    std::cout << "b conjugated: ";
    b.getConjugated().print();
    std::cout << std::endl;
}
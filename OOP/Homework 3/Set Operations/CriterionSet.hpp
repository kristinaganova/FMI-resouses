#pragma once
#include "Set.h"

template<typename T>
class CriterionSet : public Set
{
private:
    bool (*predicate)(const Vector<T>&, size_t);

public:
    CriterionSet(const Vector<T>& numbers, bool (*predicateFunc)(const Vector<T>&, size_t));
    bool contains(size_t number) const;
    const Set& merge(const Set& other) const;
    const Set& intersect(const Set& other) const;
    void print() const;
};

template<typename T>
CriterionSet<T>::CriterionSet(const Vector<T>& numbers, bool (*predicateFunc)(const Vector<T>&, size_t))
{
    for (const auto& number : numbers)
    {
        if (predicateFunc(numbers, number))
        {
            addNumber(number);
        }
    }
}

template<typename T>
bool CriterionSet<T>::contains(size_t number) const
{
    return isBitSet(number);
}

template<typename T>
const Set& CriterionSet<T>::merge(const Set& other) const
{
    throw std::logic_error("Cannot merge criterion sets.");
}

template<typename T>
const Set& CriterionSet<T>::intersect(const Set& other) const
{
    throw std::logic_error("Cannot intersect criterion sets.");
}

template<typename T>
void CriterionSet<T>::print() const
{
    std::cout << "Criterion Set: { ";

    for (size_t i = 0; i < numbers.getSize(); ++i)
    {
        if (contains(numbers[i]))
        {
            std::cout << numbers[i] << " ";
        }
    }

    std::cout << "}" << std::endl;
}

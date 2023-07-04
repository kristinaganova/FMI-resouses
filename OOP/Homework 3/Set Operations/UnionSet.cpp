#include "UnionSet.h"

const Set& UnionSet::intersect(const Set& other) const
{
    throw std::logic_error("Intersection operation not supported for UnionSet.");
}

UnionSet::UnionSet(const Vector<const Set*>& sets)
{
    if (sets.empty())
    {
        return;
    }

    const Set* firstSet = sets[0];
    numbers = firstSet->getNumbers();

    for (size_t i = 1; i < sets.getSize(); i++)
    {
        const Set* currentSet = sets[i];

        for (size_t j = 0; j < numbers.getSize(); j++)
        {
            numbers[j] |= currentSet->getNumbers()[j];
        }
    }
}

bool UnionSet::contains(size_t number) const
{
    return isBitSet(number);
}

const Set& UnionSet::merge(const Set& other) const
{
    Vector<const Set*> sets;
    sets.pushBack(this);
    sets.pushBack(&other);

    UnionSet* result = new UnionSet(sets);
    return *result;
}

void UnionSet::print() const
{
    std::cout << "Union set: { ";
    bool firstElement = true;
    for (size_t i = 0; i < numbers.getSize(); i++)
    {
        if (isBitSet(i))
        {
            if (!firstElement)
                std::cout << ", ";
            std::cout << i;
            firstElement = false;
        }
    }
    std::cout << " }" << std::endl;
}
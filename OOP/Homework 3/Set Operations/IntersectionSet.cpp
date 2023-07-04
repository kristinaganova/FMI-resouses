#include "IntersectionSet.h"

IntersectionSet::IntersectionSet(const Vector<const Set*>& sets)
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
            numbers[j] &= currentSet->getNumbers()[j];
        }
    }
}

bool IntersectionSet::contains(size_t number) const
{
    return isBitSet(number);
}

const Set& IntersectionSet::merge(const Set& other) const
{
	throw std::logic_error("Cannot merge with intersection set.");
}

const Set& IntersectionSet::intersect(const Set& other) const
{
    Vector<const Set*> sets;
    sets.pushBack(this);
    sets.pushBack(&other);

    IntersectionSet* result = new IntersectionSet(sets);
    return *result;
}

void IntersectionSet::print() const
{
    if (sets.empty())
    {
        std::cout << "Empty intersection set" << std::endl;
        return;
    }

    std::cout << "Intersection set: { ";
    bool firstElement = true;
    for (size_t i = 0; i < numbers.getSize(); i++)
    {
        if (numbers[i] != 0)
        {
            bool presentInAllSets = true;
            for (size_t j = 0; j < sets.getSize(); j++)
            {
                if (!sets[j]->contains(i))
                {
                    presentInAllSets = false;
                    break;
                }
            }

            if (presentInAllSets)
            {
                if (!firstElement)
                    std::cout << ", ";
                std::cout << i;
                firstElement = false;
            }
        }
    }
    std::cout << " }" << std::endl;
}
#pragma once
#include "Set.h"

class UnionSet : public Set
{
public:
    UnionSet(const Vector<const Set*>& sets);

    bool contains(size_t number) const override;
    const Set& merge(const Set& other) const override;

    void print() const override;

    const Set& intersect(const Set& other) const override;
};
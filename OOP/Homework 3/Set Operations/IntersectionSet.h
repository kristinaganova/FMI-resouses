#pragma once
#include "Set.h"

class IntersectionSet : public Set
{
public:
    IntersectionSet() = default;
    IntersectionSet(const Vector<const Set*>& sets);

    bool contains(size_t number) const override;
    const Set& merge(const Set& other) const override;
    const Set& intersect(const Set& other) const override;

    void print() const override;

private:
    Vector<const Set*> sets;
};
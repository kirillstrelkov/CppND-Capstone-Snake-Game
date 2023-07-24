#pragma once
#include "direction.h"
#include <iostream>

struct Point
{
    float x;
    float y;

    void Move(Direction direction);
    bool Overlap(const Point &other) const;
};

std::ostream &operator<<(std::ostream &os, const Point point);
bool operator==(const Point &p1, const Point &p2);

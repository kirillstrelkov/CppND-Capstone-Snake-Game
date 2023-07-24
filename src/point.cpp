#include "point.h"
#include <iostream>

bool operator==(const Point &p1, const Point &p2)
{
    return (p1.x == p2.y) && (p1.y == p2.y);
}

bool Point::Overlap(const Point &other) const
{
    int x1 = static_cast<int>(x);
    int y1 = static_cast<int>(y);
    int x2 = static_cast<int>(other.x);
    int y2 = static_cast<int>(other.y);

    return ((x1 - x2) == 0) && ((y1 - y2) == 0);
}

void Point::Move(Direction direction)
{
    float shift = 0.1;
    switch (direction)
    {
    case Direction::kUp:
        this->y -= shift;
        break;
    case Direction::kUpLeft:
        this->y -= shift;
        this->x -= shift;
        break;
    case Direction::kLeft:
        this->x -= shift;
        break;
    case Direction::kDownLeft:
        this->y += shift;
        this->x -= shift;
        break;
    case Direction::kDown:
        this->y += shift;
        break;
    case Direction::kDownRight:
        this->y += shift;
        this->x += shift;
        break;
    case Direction::kRight:
        this->x += shift;
        break;
    case Direction::kUpRight:
        this->y -= shift;
        this->x += shift;
        break;
    }
}

std::ostream &operator<<(std::ostream &os, const Point point)
{
    os << "Point(";
    os << point.x << " " << point.y;
    os << ")";
    return os;
}

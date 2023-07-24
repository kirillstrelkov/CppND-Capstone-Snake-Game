#pragma once

#include "point.h"
#include <cstddef>

struct Asteroid
{
    static std::size_t count;

    Point point;
    Direction direction;
    std::size_t id;
    bool is_destroyer = false;

    void Update(std::size_t grid_width, std::size_t grid_height);
    void Bounce(std::size_t border_width, std::size_t border_height);
};

std::ostream &operator<<(std::ostream &os, const Asteroid asteroid);

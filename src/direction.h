#pragma once
#include <cstddef>

enum class Direction
{
    kUp,
    kUpLeft,
    kLeft,
    kDownLeft,
    kDown,
    kDownRight,
    kRight,
    kUpRight,
};

Direction Reverse(Direction direction);

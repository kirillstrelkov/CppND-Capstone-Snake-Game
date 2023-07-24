#include "direction.h"

Direction Reverse(Direction direction)
{
    switch (direction)
    {
    case Direction::kUp:
        return Direction::kDown;
    case Direction::kUpLeft:
        return Direction::kDownRight;
    case Direction::kLeft:
        return Direction::kRight;
    case Direction::kDownLeft:
        return Direction::kUpRight;
    case Direction::kDown:
        return Direction::kUp;
    case Direction::kDownRight:
        return Direction::kUpLeft;
    case Direction::kRight:
        return Direction::kLeft;
    case Direction::kUpRight:
        return Direction::kDownLeft;
    }
    return Direction::kUp;
}

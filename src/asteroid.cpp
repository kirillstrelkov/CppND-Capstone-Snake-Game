#include "asteroid.h"
#include <cstddef>

std::size_t Asteroid::count = 0;

std::ostream &operator<<(std::ostream &os, const Asteroid asteroid)
{
    os << "Asteroid(";
    os << asteroid.id << " " << asteroid.point << " " << static_cast<int>(asteroid.direction);
    os << ")";
    return os;
}

void Asteroid::Update(std::size_t grid_width, std::size_t grid_height)
{
    point.Move(direction);
    if (point.y <= 0 || point.x <= 0 || point.y >= grid_height - 1 || point.x >= grid_width - 1)
    {
        Bounce(grid_width, grid_height);
    }
    point.Move(direction);
}

void Asteroid::Bounce(std::size_t border_width, std::size_t border_height)
{
    border_width -= 1;
    border_height -= 1;
    auto x = static_cast<int>(point.x);
    auto y = static_cast<int>(point.y);

    bool is_on_left_border = x == 0;
    bool is_on_right_border = x == border_width;
    bool is_on_top_border = y == 0;
    bool is_on_bottom_border = y == border_height;

    bool is_on_top_left_corner = is_on_top_border && is_on_left_border;
    bool is_on_top_right_corner = is_on_top_border && is_on_right_border;
    bool is_on_bottom_left_corner = is_on_bottom_border && is_on_left_border;
    bool is_on_bottom_right_corner = is_on_bottom_border && is_on_right_border;

    // Simple direction -> just reverse
    auto new_dir = Reverse(direction);
    switch (direction)
    {
    case Direction::kUpLeft:
        if (!is_on_top_left_corner)
        {
            if (is_on_left_border)
            {
                new_dir = Direction::kUpRight;
            }
            else if (is_on_top_border)
            {
                new_dir = Direction::kDownLeft;
            }
        }
        break;
    case Direction::kDownLeft:
        if (!is_on_bottom_left_corner)
        {
            if (is_on_left_border)
            {
                new_dir = Direction::kDownRight;
            }
            else if (is_on_bottom_border)
            {
                new_dir = Direction::kUpLeft;
            }
        }
        break;
    case Direction::kDownRight:
        if (!is_on_bottom_right_corner)
        {
            if (is_on_right_border)
            {
                new_dir = Direction::kDownLeft;
            }
            else if (is_on_bottom_border)
            {
                new_dir = Direction::kUpRight;
            }
        }
        break;
    case Direction::kUpRight:
        if (!is_on_top_right_corner)
        {
            if (is_on_right_border)
            {
                new_dir = Direction::kUpLeft;
            }
            else if (is_on_top_border)
            {
                new_dir = Direction::kDownRight;
            }
        }
        break;
    }
    direction = new_dir;
}

#include "ship.h"
#include "direction.h"
#include <iostream>
#include <vector>

size_t Ship::bulletCount = 0;

Ship::Ship(int grid_width, int grid_height)
    : grid_width(grid_width),
      grid_height(grid_height)
{
    head = {static_cast<float>(grid_width) / 2, static_cast<float>(grid_height) - 3};
    BuildBody();
}

void Ship::Shoot()
{
    Bullet bullet{head, direction};
    bullets[Ship::bulletCount++] = bullet;
}

bool Ship::Overlap(const Point &point)
{
    if (head.Overlap(point))
    {
        return true;
    }
    for (const auto &p : body)
    {
        Point other{static_cast<float>(p.x), static_cast<float>(p.y)};
        if (point.Overlap(other))
        {
            return true;
        }
    }
    return false;
}

void Ship::Update()
{
    SDL_Point prev_cell{
        static_cast<int>(head.x),
        static_cast<int>(head.y)}; // We first capture the head's cell before updating.
    SDL_Point current_cell{
        static_cast<int>(head.x),
        static_cast<int>(head.y)}; // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    // if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
    // {
    //     UpdateBody(current_cell, prev_cell);
    // }

    std::vector<size_t> ids_to_remove;

    for (auto &[id, bullet] : bullets)
    {
        switch (bullet.direction)
        {
        case Direction::kUp:

            bullet.point.y -= 1 * bullet_speed;
            break;
        case Direction::kDown:

            bullet.point.y += 1 * bullet_speed;
            break;
        case Direction::kLeft:

            bullet.point.x -= 1 * bullet_speed;
            break;
        case Direction::kRight:

            bullet.point.x += 1 * bullet_speed;
            break;
        }
        if (IsOnBorder(bullet.point))
        {
            ids_to_remove.push_back(id);
        }
    }

    for (auto id : ids_to_remove)
    {
        bullets.erase(bullets.find(id));
    }
}

void Ship::Move(Direction direction)
{
    auto old_direction = this->direction;
    this->direction = direction;
    if (old_direction == direction)
    {
        Shift();
    }
    else
    {
        Rotate(old_direction);
    }
}

void Ship::Rotate(Direction old_direction)
{
    int center_x = body[1].x;
    int center_y = body[1].y;

    auto &left_side = body[0];
    auto &right_side = body[2];

    auto build_body = [=]() {

    };

    switch (direction)
    {
    case Direction::kUp:
        head.x = center_x;
        head.y = center_y - 1;

        break;
    case Direction::kDown:
        head.x = center_x;
        head.y = center_y + 1;

        break;
    case Direction::kLeft:
        head.x = center_x - 1;
        head.y = center_y;

        break;
    case Direction::kRight:
        head.x = center_x + 1;
        head.y = center_y;

        break;
    }
    BuildBody(direction);
}

template <typename T>
bool Ship::IsOnBorder(T point)
{
    return point.y <= 0 || point.x <= 0 || point.y >= grid_height - 1 || point.x >= grid_width - 1;
}

void Ship::BuildBody(Direction direction)
{
    int x = static_cast<int>(head.x);
    int y = static_cast<int>(head.y);

    int size = 3;
    std::vector<int> shifts_x(size);
    std::vector<int> shifts_y(size);

    switch (direction)
    {
    case Direction::kUp:
        shifts_x = {-1, 0, 1};
        shifts_y = {1, 1, 1};
        break;
    case Direction::kDown:
        shifts_x = {-1, 0, 1};
        shifts_y = {-1, -1, -1};
        break;
    case Direction::kLeft:
        shifts_x = {1, 1, 1};
        shifts_y = {-1, 0, 1};
        break;
    case Direction::kRight:
        shifts_x = {-1, -1, -1};
        shifts_y = {-1, 0, 1};
        break;
    }

    for (int i = 0; i < size; i++)
    {
        body[i].x = x + shifts_x[i];
        body[i].y = y + shifts_y[i];
    }
}

void Ship::Shift()
{
    if (IsOnBorder<SDL_Point>({static_cast<int>(head.x), static_cast<int>(head.y)}))
    {
        return;
    }

    auto moveByOne = [=](bool use_x, int shift)
    {
        (use_x ? head.x : head.y) += shift;
        for (auto &p : body)
        {
            (use_x ? p.x : p.y) += shift;
        }
    };
    switch (direction)
    {
    case Direction::kUp:
        moveByOne(false, -1);
        break;
    case Direction::kDown:
        moveByOne(false, +1);
        break;
    case Direction::kLeft:
        moveByOne(true, -1);
        break;
    case Direction::kRight:
        moveByOne(true, +1);
        break;
    }
}

bool Ship::ShipCell(int x, int y)
{
    if (x == static_cast<int>(head.x) && y == static_cast<int>(head.y))
    {
        return true;
    }
    for (auto const &item : body)
    {
        if (x == item.x && y == item.y)
        {
            return true;
        }
    }
    return false;
}
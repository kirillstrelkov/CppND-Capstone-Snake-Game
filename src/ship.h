#pragma once

#include <array>
#include <vector>
#include <unordered_map>
#include "SDL.h"
#include "point.h"
#include "direction.h"

class Ship
{

public:
    struct Bullet
    {
        Point point;
        Direction direction;
    };

    Ship(int grid_width, int grid_height);

    void Update();
    bool ShipCell(int x, int y);
    void Move(Direction direction);
    void Shoot();
    bool Overlap(const Point &point);

    Direction direction = Direction::kUp;
    static size_t bulletCount;
    const float bullet_speed{0.1};
    bool alive{true};
    Point head;
    std::array<SDL_Point, 3> body;
    std::unordered_map<size_t, Bullet> bullets;

private:
    void Rotate(Direction old_direction);
    void Shift();

    void BuildBody(Direction direction = Direction::kUp);

    template <typename T>
    bool IsOnBorder(T point);

    bool growing{false};
    int grid_width;
    int grid_height;
};
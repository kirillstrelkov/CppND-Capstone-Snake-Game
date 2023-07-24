#pragma once

#include "ship.h"
#include "direction.h"

class Controller
{
public:
    void HandleInput(bool &running, Ship &ship) const;

private:
    void ChangeDirection(Ship &ship, Direction input,
                         Direction opposite) const;
};

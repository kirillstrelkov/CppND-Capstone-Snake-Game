#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "ship.h"
#include "direction.h"

void Controller::ChangeDirection(Ship &ship, Direction input,
                                 Direction opposite) const
{
  if (ship.direction != opposite)
  {
    ship.Move(input);
  }
  return;
}

void Controller::HandleInput(bool &running, Ship &ship) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN && ship.alive)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        ChangeDirection(ship, Direction::kUp,
                        Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(ship, Direction::kDown,
                        Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(ship, Direction::kLeft,
                        Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(ship, Direction::kRight,
                        Direction::kLeft);
        break;

      case SDLK_SPACE:
        ship.Shoot();
        break;
      }
    }
  }
}
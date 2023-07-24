#pragma once

#include <random>
#include <memory>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "ship.h"
#include "asteroid.h"
#include "renderer.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t initial_asteroids);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;

private:
  std::mutex mtx;
  std::unique_ptr<Ship> ship;
  std::vector<Asteroid> asteroids;

  std::size_t grid_width;
  std::size_t grid_height;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_dir;

  int score{0};

  // void PlaceFood();
  void AddAsteroid();
  void Update();
};

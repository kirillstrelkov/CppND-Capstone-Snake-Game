#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <mutex>
#include "game.h"
#include "direction.h"
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t initial_asteroids)
    : grid_width(grid_width),
      grid_height(grid_height),
      engine(dev()),
      random_w(1, static_cast<int>(grid_width / 2)),
      random_h(1, static_cast<int>(grid_height / 2)),
      random_dir(0, static_cast<int>(Direction::kUpRight))
{
  ship = std::make_unique<Ship>(grid_width, grid_height);
  for (std::size_t i = 0; i < initial_asteroids; i++)
  {
    AddAsteroid();
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::thread thead_asteroids([this, &running]()
                              {

        int prev_score = GetScore();
        while (running && ship->alive)
        {
          std::this_thread::sleep_for(std::chrono::seconds(1));

          int cur_score = GetScore();
          if (cur_score != prev_score)
          {
            std::lock_guard<std::mutex> lock(mtx);

            for (int i = 0; i < cur_score - prev_score + 1; i++)
            {
              AddAsteroid();
            }
            prev_score = cur_score;
          }
        } });

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *ship);
    Update();
    renderer.Render(*ship, asteroids);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  thead_asteroids.join();
}

void Game::AddAsteroid()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);

    // new point is on free space
    if (!ship->ShipCell(x, y))
    {
      break;
    }
  }
  Direction dir = static_cast<Direction>(random_dir(engine));
  Asteroid asteroid{{static_cast<float>(x), static_cast<float>(y)}, dir, Asteroid::count++};
  asteroids.push_back(asteroid);
}

void Game::Update()
{
  if (!ship->alive)
    return;

  ship->Update();

  std::lock_guard<std::mutex> lock(mtx);

  std::unordered_set<std::size_t> asteroid_ids_to_remove;
  std::unordered_set<std::size_t> bullet_ids_to_remove;

  for (auto &asteroid : asteroids)
  {
    bool is_asteroid_alive = true;

    for (const auto &[bullet_id, bullet] : ship->bullets)
    {
      if (asteroid.point.Overlap(bullet.point))
      {
        asteroid_ids_to_remove.insert(asteroid.id);
        bullet_ids_to_remove.insert(asteroid.id);

        is_asteroid_alive = false;
        break;
      }
    }

    if (is_asteroid_alive)
    {
      asteroid.Update(grid_width, grid_height);

      if (ship->Overlap(asteroid.point))
      {
        asteroid.is_destroyer = true;
        ship->alive = false;
        break;
      }
    }
  }

  // collapsed asteroids should bounce in random directions
  for (auto &asteroid : asteroids)
  {
    for (auto &asteroid2 : asteroids)
    {
      if ((asteroid.id != asteroid2.id) && asteroid.point.Overlap(asteroid2.point))
      {
        for (auto &ast : {&asteroid, &asteroid2})
        {
          Direction new_dir = static_cast<Direction>(random_dir(engine));
          ast->direction = new_dir;
          ast->Update(grid_width, grid_height);
        }
      }
    }
  }

  // remove destroyed asteroids
  asteroids.erase(remove_if(asteroids.begin(), asteroids.end(), [&asteroid_ids_to_remove](const auto &asteroid)
                            { return asteroid_ids_to_remove.find(asteroid.id) != asteroid_ids_to_remove.end(); }),
                  asteroids.end());

  // remove bullets that hit asteroids
  for (auto it = bullet_ids_to_remove.begin(); it != bullet_ids_to_remove.end(); it++)
  {
    ship->bullets.erase(*it);
  }

  score += asteroid_ids_to_remove.size();
}

int Game::GetScore() const
{
  return score;
}

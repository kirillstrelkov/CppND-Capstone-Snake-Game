#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Ship Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const Ship &ship, const std::vector<Asteroid> &asteroids)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render ship's bullets
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
  for (auto const &bullet : ship.bullets)
  {
    const auto &point = bullet.second.point;
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render ship's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : ship.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render ship's head
  block.x = static_cast<int>(ship.head.x) * block.w;
  block.y = static_cast<int>(ship.head.y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render asteroids
  SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x80, 0x80, 0xFF);
  for (auto const &asteroid : asteroids)
  {
    const auto &point = asteroid.point;
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  if (!ship.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    for (auto const &asteroid : asteroids)
    {
      if (asteroid.is_destroyer)
      {
        const auto &point = asteroid.point;
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
        break;
      }
    }
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Ship Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

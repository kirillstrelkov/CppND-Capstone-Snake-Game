#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

std::unordered_map<std::string, std::size_t> ReadConfig()
{
  std::unordered_map<std::string, std::size_t> data;
  std::ifstream infile("data/game.cfg");
  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss(line);
    std::string key;
    std::size_t value;
    if (!(iss >> key >> value))
    {
      break;
    }
    data[key] = value;
  }

  return std::move(data);
}

int main()
{
  auto config = std::move(ReadConfig());
  const std::size_t kFramesPerSecond{config["fps"]};
  const std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  const std::size_t kScreenWidth{config["screen_width"]};
  const std::size_t kScreenHeight{config["screen_height"]};
  const std::size_t kGridWidth{config["grid_width"]};
  const std::size_t kGridHeight{config["grid_height"]};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, config["initial_asteroids"]);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}
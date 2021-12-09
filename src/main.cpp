#include <iostream>

#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{840};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Game game;
  game.Run(renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  return 0;
}
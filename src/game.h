#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "renderer.h"
//#include "snake.h"

class Game {
 public:
  Game();
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  //void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;

 private:
  //Snake snake;
  //SDL_Point food;

  int score{0};

  void Update();
};

#endif
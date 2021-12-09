#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>

class Renderer {
 public:
  Renderer(int framesPerSecond, const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  //void Render(Snake const snake, SDL_Point const &food1, SDL_Point const &food2, SDL_Point const &food3);
  void Render();
  void UpdateWindowTitle(int score, int health, int seconds);
  int GetQuadrant(float rads);

  // Must be public
  SDL_Window *window;
  SDL_Renderer *renderer;

 private:
  int framesPerSecond;
  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif
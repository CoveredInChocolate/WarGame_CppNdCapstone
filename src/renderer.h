#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
//#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  //void Render(Snake const snake, SDL_Point const &food1, SDL_Point const &food2, SDL_Point const &food3);
  void Render();
  void UpdateWindowTitle(int score, int health);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  //SDL_Surface *sdl_surf;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif
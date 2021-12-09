#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>  

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("!! WarGame !!", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render() {
    // Clear screen
    SDL_RenderClear(sdl_renderer);

    // Render food
    /*
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_Rect block;
    block.w = 20;
    block.h = 20;
    block.x = 5;
    block.y = 5;
    SDL_RenderFillRect(sdl_renderer, &block);
    */

    //SDL_Surface * grassImage = SDL_LoadBMP("assets/grass4.bmp");
    SDL_Surface * grassImage = SDL_LoadBMP("grass4.bmp");
    SDL_Texture * grassTexture = SDL_CreateTextureFromSurface(sdl_renderer, grassImage);

    SDL_Rect drect_grass1 = { 0, 0, 640, 420 };
    SDL_Rect drect_grass2 = { 640, 0, 640, 420 };
    SDL_Rect drect_grass3 = { 0, 420, 640, 420 };
    SDL_Rect drect_grass4 = { 640, 420, 640, 420 };

    // GRASS
    SDL_RenderCopy(sdl_renderer, grassTexture, NULL, &drect_grass1);
    SDL_RenderCopy(sdl_renderer, grassTexture, NULL, &drect_grass2);
    SDL_RenderCopy(sdl_renderer, grassTexture, NULL, &drect_grass3);
    SDL_RenderCopy(sdl_renderer, grassTexture, NULL, &drect_grass4);
    std::cout << "DOES NOT SHOW RENDER!! THEN FORGET IT!\n";

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

/*
void Renderer::Render(Snake const snake, SDL_Point const &food1,
SDL_Point const &food2, SDL_Point const &food3) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x05, 0x05, 0x05, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render grassy background
  SDL_Surface * image = SDL_LoadBMP("assets/grass.bmp");
  SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, image);
  SDL_Rect dstrect = { 5, 5, 64, 64 };
  SDL_RenderCopy(sdl_renderer, texture, NULL, &dstrect);
  //SDL_RenderCopy(sdl_renderer, texture, NULL, NULL);
  //SDL_RenderPresent(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food1.x * block.w;
  block.y = food1.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food2.x * block.w;
  block.y = food2.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food3.x * block.w;
  block.y = food3.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
*/

void Renderer::UpdateWindowTitle(int score, int health) {
  std::string title{"!! WarGame !! -- Marines killed: " + std::to_string(score) + " Turret Health: " + std::to_string(health)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

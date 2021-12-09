#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game() {
  //PlaceFood();
}

//void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    Uint32 buttons; // Capture mouse
    int mouse_x, mouse_y;
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != NULL) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        // Mouse stats
        SDL_PumpEvents();  // make sure we have the latest mouse state.
        buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
        //SDL_Log("Mouse cursor is at %d, %d", mouse_x, mouse_y);
        Update();
        renderer.Render();
        //renderer.Render(snake, food);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(0, 100);
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}


void Game::Update() {
    /*
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
    */
}

int Game::GetScore() const { return score; }
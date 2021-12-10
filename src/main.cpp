#include <SDL2/SDL.h>
#include "renderer.h"  
#include <iostream>
#include <cmath>
#include <thread>

// --- Compilation:
// make all
// ./WarGame


int main(int argc, char ** argv) {
    std::cout << "Starting program!\n";

    int framesPerSecond = 30;
    const std::size_t  screen_width = 1280;
    const std::size_t  screen_height = 840;

    Renderer game(framesPerSecond, screen_width, screen_height);
    game.Render();

    std::cout << "Program terminating...\n";

    return 0;
}
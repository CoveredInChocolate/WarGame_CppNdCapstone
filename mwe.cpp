// Experimentation - minimal working examples
/*
Compile with:
g++ -lSDL2main -lSDL2 mwe.cpp;./a.out
Does not work:
g++ -std=c++17 mwe.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image;./a.out
*/

#include <SDL2/SDL.h>  
#include <iostream>

/*
int main() {
    std::cout << "This is some text\n\n";
}
*/
//#include <SDL.h>

/*
int main(int argc, char ** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * screen = SDL_CreateWindow("My SDL Empty Window",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 
    SDL_Quit();
 
    return 0;
}
*/

int main(int argc, char ** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
 
    // game code eventually goes here
 
    SDL_Quit();
 
    return 0;
}

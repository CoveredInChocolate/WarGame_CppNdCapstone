#include "renderer.h"
#include "turret.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>  

Renderer::Renderer(int framesPerSecond,
                   const std::size_t screen_width,
                   const std::size_t screen_height)
    : framesPerSecond(framesPerSecond),
      screen_width(screen_width),
      screen_height(screen_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    window = SDL_CreateWindow("!! WarGame !! -- Marines killed: 0, Turret Health: 100",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Render() {

    // -------------------------- Various constants and variables
    std::size_t target_frame_duration{1000 / framesPerSecond};
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int durationSeconds = 0;

    Uint32 buttons;
    int xcoord, ycoord;
    int xcorr, ycorr;
    int QUADRANT;


    // -------------------------- Load assets and sprites
    // Grass
    SDL_Surface * grassImage = SDL_LoadBMP("assets/grass4.bmp");
    SDL_Texture * grassTexture = SDL_CreateTextureFromSurface(renderer, grassImage);
    SDL_FreeSurface(grassImage);

    // Resizing
    SDL_Rect gr1rect = { 0, 0, 640, 420 };
    SDL_Rect gr2rect = { 640, 0, 640, 420 };
    SDL_Rect gr3rect = { 0, 420, 640, 420 };
    SDL_Rect gr4rect = { 640, 420, 640, 420 };

    // Add trees
    SDL_Surface * tree1 = SDL_LoadBMP("assets/tree1.bmp");
    SDL_Surface * tree2 = SDL_LoadBMP("assets/tree2.bmp");
    SDL_Surface * tree3 = SDL_LoadBMP("assets/tree3.bmp");
    SDL_Texture * tree1text = SDL_CreateTextureFromSurface(renderer, tree1);
    SDL_Texture * tree2text = SDL_CreateTextureFromSurface(renderer, tree2);
    SDL_Texture * tree3text = SDL_CreateTextureFromSurface(renderer, tree3);
    SDL_FreeSurface(tree1);
    SDL_FreeSurface(tree2);
    SDL_FreeSurface(tree3);
    SDL_Rect t1rect = { 154, 185, 240, 240 };
    SDL_Rect t2rect = { 825, 94, 240, 240 };
    SDL_Rect t3rect = { 915, 523, 240, 240 };

    // Turret
    Turret turret(1000, 90, 0.7);
    int gunSize = turret.GetGunSize();
    SDL_Surface * gg = SDL_LoadBMP("assets/gluegun_anim.bmp");
    SDL_Texture * ggText = SDL_CreateTextureFromSurface(renderer, gg);
    SDL_FreeSurface(gg);

    // Muzzle Flash
    SDL_Surface * mzImgWW = SDL_LoadBMP("assets/muzzle_WW.bmp");
    SDL_Surface * mzImgNW = SDL_LoadBMP("assets/muzzle_NW.bmp");
    SDL_Surface * mzImgNN = SDL_LoadBMP("assets/muzzle_NN.bmp");
    SDL_Surface * mzImgNE = SDL_LoadBMP("assets/muzzle_NE.bmp");
    SDL_Surface * mzImgEE = SDL_LoadBMP("assets/muzzle_EE.bmp");
    SDL_Surface * mzImgSE = SDL_LoadBMP("assets/muzzle_SE.bmp");
    SDL_Surface * mzImgSS = SDL_LoadBMP("assets/muzzle_SS.bmp");
    SDL_Surface * mzImgSW = SDL_LoadBMP("assets/muzzle_SW.bmp");
    SDL_Texture * mzWW = SDL_CreateTextureFromSurface(renderer, mzImgWW);
    SDL_Texture * mzNW = SDL_CreateTextureFromSurface(renderer, mzImgNW);
    SDL_Texture * mzNN = SDL_CreateTextureFromSurface(renderer, mzImgNN);
    SDL_Texture * mzNE = SDL_CreateTextureFromSurface(renderer, mzImgNE);
    SDL_Texture * mzEE = SDL_CreateTextureFromSurface(renderer, mzImgEE);
    SDL_Texture * mzSE = SDL_CreateTextureFromSurface(renderer, mzImgSE);
    SDL_Texture * mzSS = SDL_CreateTextureFromSurface(renderer, mzImgSS);
    SDL_Texture * mzSW = SDL_CreateTextureFromSurface(renderer, mzImgSW);
    SDL_FreeSurface(mzImgWW);
    SDL_FreeSurface(mzImgNW);
    SDL_FreeSurface(mzImgNN);
    SDL_FreeSurface(mzImgNE);
    SDL_FreeSurface(mzImgEE);
    SDL_FreeSurface(mzImgSE);
    SDL_FreeSurface(mzImgSS);
    SDL_FreeSurface(mzImgSW);
    SDL_Texture * mzlAN = mzNN;
    // std::vector<SDL_Texture*> mzlAN;
    // mzlAN.emplace_back(mzWW);
    // mzlAN.emplace_back(mzNW);
    // mzlAN.emplace_back(mzNN);
    std::vector<SDL_Texture*> mzlANV = {mzWW, mzNW, mzNN, mzNE, mzEE, mzSE, mzSS, mzSW};
    // std::cout << "ORIG VAL: " << mzNN << "\n";
    // std::cout << "VECT VAL: " << mzlANV << "\n";

    // Points North by default
    std::vector<int> gunSource = turret.GetTextureSource(3);
    std::vector<int> gunDest = turret.GetTextureDestination(3);
    SDL_Rect gunSRC = { gunSource[0], gunSource[1], gunSource[2], gunSource[3] };
    SDL_Rect gunDST = { gunDest[0], gunDest[1], gunDest[2], gunDest[3] };
    std::vector<int> muzzleSource = turret.GetMuzzleSource(3);
    std::vector<int> muzzleDest = turret.GetMuzzleDestination(3);
    SDL_Rect mzlSRC = { muzzleSource[0], muzzleSource[1], muzzleSource[2], muzzleSource[3] };
    SDL_Rect mzlDST = { muzzleDest[0], muzzleDest[1], muzzleDest[2], muzzleDest[3] };
    //std::cout << "VALS: " << gunSource << "\n";
    // for ( int i = 0; i < 4; i++ ) {
    //   std::cout << "VALS: ";
    //   std::cout << gunSource[i] << "\n";
    // }



    // ----------------------------------------------------- MAIN GAME LOOP
    while (!quit) {
        while (SDL_PollEvent(&event) != NULL) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        frame_start = SDL_GetTicks();

        // Mouse stats
        SDL_PumpEvents();  // make sure we have the latest mouse state.
        buttons = SDL_GetMouseState(&xcoord, &ycoord);
        
        // Calculating corrected points: (0,0) in the center
        xcorr = xcoord - screen_width/2;
        ycorr = ycoord - screen_height/2;

        // Polar coordinates, more specifically: radians, to find angle
        float rads = atan2(ycorr, xcorr);
        //SDL_Log("Mouse cursor is at %f radians", rads);

        QUADRANT = GetQuadrant(rads);
        //std::cout << "QUAD: " << QUADRANT << "\n";

        // Clear screen
        SDL_RenderClear(renderer);

        // GRASS
        SDL_RenderCopy(renderer, grassTexture, NULL, &gr1rect);
        SDL_RenderCopy(renderer, grassTexture, NULL, &gr2rect);
        SDL_RenderCopy(renderer, grassTexture, NULL, &gr3rect);
        SDL_RenderCopy(renderer, grassTexture, NULL, &gr4rect);
        // TREES
        SDL_RenderCopy(renderer, tree1text, NULL, &t1rect);
        SDL_RenderCopy(renderer, tree2text, NULL, &t2rect);
        SDL_RenderCopy(renderer, tree3text, NULL, &t3rect);
        // TURRET
        gunSource = turret.GetTextureSource(QUADRANT);
        gunDest = turret.GetTextureDestination(QUADRANT);
        gunSRC = { gunSource[0], gunSource[1], gunSource[2], gunSource[3] };
        gunDST = { gunDest[0], gunDest[1], gunDest[2], gunDest[3] };
        SDL_RenderCopy(renderer, ggText, &gunSRC, &gunDST);
        // MUZZLE FLASH
        muzzleSource = turret.GetMuzzleSource(QUADRANT);
        muzzleDest = turret.GetMuzzleDestination(QUADRANT);
        mzlSRC = { muzzleSource[0], muzzleSource[1], muzzleSource[2], muzzleSource[3] };
        mzlDST = { muzzleDest[0], muzzleDest[1], muzzleDest[2], muzzleDest[3] };
        if ((buttons & SDL_BUTTON_LMASK) != 0) {
            //SDL_Log("Mouse Button 1 (left) is pressed.");
            mzlAN = mzlANV[QUADRANT-1];
            SDL_RenderCopy(renderer, mzlAN, &mzlSRC, &mzlDST);
        }
        // MARINES
        //...

        // Update Screen
        SDL_RenderPresent(renderer);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            durationSeconds = durationSeconds + 1;
            UpdateWindowTitle(0, turret.GetHitPoints(), durationSeconds);
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

void Renderer::UpdateWindowTitle(int score, int health, int seconds) {
  std::string title{"!! WarGame !! -- Marines killed: " + std::to_string(score) + ", Turret Health: " + std::to_string(health) + ", Run Time: " + std::to_string(seconds)};
  SDL_SetWindowTitle(window, title.c_str());
}

int Renderer::GetQuadrant(float rads) {

    int QUAD;

    // Define quadrants
    if (rads > 7*M_PI/8 || rads < -7*M_PI/8) {
        //SDL_Log("Quadrant WW");
        QUAD = 1;
    } else if (rads < -5*M_PI/8 && rads > -7*M_PI/8) {
        //SDL_Log("Quadrant NW");
        QUAD = 2;
    } else if (rads < -3*M_PI/8 && rads > -5*M_PI/8) {
        //SDL_Log("Quadrant NN");
        QUAD = 3;
    } else if (rads < -M_PI/8 && rads > -3*M_PI/8) {
        //SDL_Log("Quadrant NE");
        QUAD = 4;
    } else if (rads < M_PI/8 && rads > -M_PI/8) {
        //SDL_Log("Quadrant EE");
        QUAD = 5;
    } else if(rads > M_PI/8 && rads < 3*M_PI/8) {
        //SDL_Log("Quadrant SE");
        QUAD = 6;
    } else if(rads > 3*M_PI/8 && rads < 5*M_PI/8) {
        //SDL_Log("Quadrant SS");
        QUAD = 7;
    } else if(rads > 5*M_PI/8 && rads < 7*M_PI/8) {
        //SDL_Log("Quadrant SW");
        QUAD = 8;
    } else {
        //SDL_Log("Quadrant XX");
        QUAD = 3;
    }

    return(QUAD);
}

/*
    // Clear screen
    SDL_RenderClear(renderer);

    // Render food
    /*
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_Rect block;
    block.w = 20;
    block.h = 20;
    block.x = 5;
    block.y = 5;
    SDL_RenderFillRect(renderer, &block);
    * /

    //SDL_Surface * grassImage = SDL_LoadBMP("assets/grass4.bmp");
    SDL_Surface * grassImage = SDL_LoadBMP("grass4.bmp");
    SDL_Texture * grassTexture = SDL_CreateTextureFromSurface(renderer, grassImage);

    SDL_Rect drect_grass1 = { 0, 0, 640, 420 };
    SDL_Rect drect_grass2 = { 640, 0, 640, 420 };
    SDL_Rect drect_grass3 = { 0, 420, 640, 420 };
    SDL_Rect drect_grass4 = { 640, 420, 640, 420 };

    // GRASS
    SDL_RenderCopy(renderer, grassTexture, NULL, &drect_grass1);
    SDL_RenderCopy(renderer, grassTexture, NULL, &drect_grass2);
    SDL_RenderCopy(renderer, grassTexture, NULL, &drect_grass3);
    SDL_RenderCopy(renderer, grassTexture, NULL, &drect_grass4);
    std::cout << "DOES NOT SHOW RENDER!! THEN FORGET IT!\n";

    // Update Screen
    SDL_RenderPresent(renderer);
}
*/


/*
void Renderer::Render(Snake const snake, SDL_Point const &food1,
SDL_Point const &food2, SDL_Point const &food3) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(renderer, 0x05, 0x05, 0x05, 0xFF);
  SDL_RenderClear(renderer);

  // Render grassy background
  SDL_Surface * image = SDL_LoadBMP("assets/grass.bmp");
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_Rect dstrect = { 5, 5, 64, 64 };
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);
  //SDL_RenderCopy(renderer, texture, NULL, NULL);
  //SDL_RenderPresent(renderer);

  // Render food
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food1.x * block.w;
  block.y = food1.y * block.h;
  SDL_RenderFillRect(renderer, &block);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food2.x * block.w;
  block.y = food2.y * block.h;
  SDL_RenderFillRect(renderer, &block);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food3.x * block.w;
  block.y = food3.y * block.h;
  SDL_RenderFillRect(renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(renderer, &block);

  // Update Screen
  SDL_RenderPresent(renderer);
}
*/


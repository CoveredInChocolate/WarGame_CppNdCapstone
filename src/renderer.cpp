#include "renderer.h"
#include "turret.h"
#include "marine.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unistd.h>
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
    int MAXMARINES = 5;
    std::size_t target_frame_duration{1000 / framesPerSecond};
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    Uint32 attackInterval;
    int durationSeconds = 0;

    Uint32 buttons;
    int xcoord, ycoord;
    int xcorr, ycorr;
    int marineKills = 0;
    int QUADRANT;
    int attackingMarines = 0;

    // Hitbox variale
    std::vector<int> hitbox;

    // Display some debugging info
    bool DEBUG = false;


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

    // Explosion
    float explosionSize = 0.6;
    SDL_Surface * govr = SDL_LoadBMP("assets/GameOver.bmp");
    SDL_Texture * goverText = SDL_CreateTextureFromSurface(renderer, govr);
    SDL_Rect srcrectGover = { 5, 5, 390, 320 };
    SDL_Rect dstrectGover = { 540, 230, explosionSize*321, explosionSize*385 };

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
    std::vector<SDL_Texture*> mzlANV = {mzWW, mzNW, mzNN, mzNE, mzEE, mzSE, mzSS, mzSW};

    // Points North by default
    std::vector<int> gunSource = turret.GetTextureSource(3);
    std::vector<int> gunDest = turret.GetTextureDestination(3);
    SDL_Rect gunSRC = { gunSource[0], gunSource[1], gunSource[2], gunSource[3] };
    SDL_Rect gunDST = { gunDest[0], gunDest[1], gunDest[2], gunDest[3] };
    std::vector<int> muzzleSource = turret.GetMuzzleSource(3);
    std::vector<int> muzzleDest = turret.GetMuzzleDestination(3);
    SDL_Rect mzlSRC = { muzzleSource[0], muzzleSource[1], muzzleSource[2], muzzleSource[3] };
    SDL_Rect mzlDST = { muzzleDest[0], muzzleDest[1], muzzleDest[2], muzzleDest[3] };

    SDL_Surface * mimg = SDL_LoadBMP("assets/scmarine_cut_mirror_shadows.bmp");
    SDL_Texture * mrnText = SDL_CreateTextureFromSurface(renderer, mimg);
    SDL_FreeSurface(mimg);

    // Initializing Marine vectors and helper vectors
    std::vector<Marine> marines;
    std::vector<Marine> splat;
    std::vector<int> removeMarines;
    std::vector<int> removeDead;

    // // Starting Position
    // std::vector<int> pos = RandomPoint();
    // float ddd = GetDist(pos[0], pos[1]);
    // std::cout << "xPos: " << pos[0] << "\n";
    // std::cout << "yPos: " << pos[1] << "\n";
    // std::cout << "QUAD: " << pos[2] << "\n";
    // std::cout << "dist: " << ddd << "\n";

    // How many milliseconds between spawns (on average)
    int spawnRate = 800;
    // How quicly the rate increases (i.e. time reduces)
    float spawnRateDecrease = 0.9;
    // Initialize random number generator and draw first spawn time
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(100, spawnRate); // define the range

    // First marine spawn
    int nextSpawnTime = distr(gen);

    // Spawm two marines straight away
    std::vector<int> pos;
    // Starting Position
    pos = RandomPoint();
    Marine m(pos[0], pos[1], pos[2]);
    std::vector<int> mSource = m.GetTextureSource(frame_start);
    std::vector<int> mDest = m.GetTextureDestination();
    SDL_Rect mSRC = { mSource[0], mSource[1], mSource[2], mSource[3] };
    SDL_Rect mDST = { mDest[0], mDest[1], mDest[2], mDest[3] };
    
    // Starting Position
    pos = RandomPoint();
    Marine m2(pos[0], pos[1], pos[2]);
    mSource = m2.GetTextureSource(frame_start);
    mDest = m2.GetTextureDestination();
    mSRC = { mSource[0], mSource[1], mSource[2], mSource[3] };
    mDST = { mDest[0], mDest[1], mDest[2], mDest[3] };

    marines = {m, m2};



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
        //float rads = atan2(ycorr, xcorr);
        float rads = GetRadians(xcorr, ycorr);
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
        for(auto & mrn : marines) {
            mrn.UpdatePosition(frame_start);
            mSource = mrn.GetTextureSource(frame_start);
            mDest = mrn.GetTextureDestination();
            mSRC = { mSource[0], mSource[1], mSource[2], mSource[3] };
            mDST = { mDest[0], mDest[1], mDest[2], mDest[3] };
            SDL_RenderCopy(renderer, mrnText, &mSRC, &mDST);
        }
        for(auto & mrn : splat) {
            mSource = mrn.GetDeathSource(frame_start);
            mDest = mrn.GetDeathDestination(frame_start);
            mSRC = { mSource[0], mSource[1], mSource[2], mSource[3] };
            mDST = { mDest[0], mDest[1], mDest[2], mDest[3] };
            SDL_RenderCopy(renderer, mrnText, &mSRC, &mDST);
        }
        // Spawn new marine
        if (frame_start > nextSpawnTime) {
            pos = RandomPoint();
            Marine m(pos[0], pos[1], pos[2]);
            m.setSpawnTime(frame_start);
            marines.push_back(m);

            // Define next spawn time
            nextSpawnTime = frame_start + distr(gen);
        }

        // Check hitboxes;
        if ((buttons & SDL_BUTTON_LMASK) != 0) {
            for(auto & mrn : marines) {
                if(mrn.isAlive()) {
                    hitbox = mrn.GetTextureDestination();
                    if (hitbox[0] < xcoord && hitbox[0] + hitbox[2] > xcoord && hitbox[1] < ycoord && hitbox[1] + hitbox[3] > ycoord) {
                        //std::cout << "HIT!\n";
                        mrn.setAliveFalse();
                        mrn.setTimeOfDeath(frame_start);
                        marineKills = marineKills + 1;
                        splat.push_back(mrn); // Marine to death animation
                    }
                }
            }
        }

        // Count attacking marines and deducting hitpoints
        if(frame_start - attackInterval > 250) {
            attackingMarines = 0;
            for(int k = 0; k < marines.size(); k++) {
                if (marines[k].isAttacking() == 1) {
                    attackingMarines = attackingMarines + 1;
                }
            }
            turret.SetHitPoints(attackingMarines);
            if (turret.GetHitPoints() <= 0) {
                // Sleep for 10 seconds and quit
                UpdateWindowTitle(marineKills, marines.size(), 0, durationSeconds);
                SDL_RenderCopy(renderer, goverText, &srcrectGover, &dstrectGover);
                SDL_RenderPresent(renderer);
                sleep(10);
                PrintGameOver(marineKills, durationSeconds);
                quit = true;
            }
            attackInterval = frame_start;
        }

        // Cleaning up marines vector
        // Finding indices to remove
        for(int i = 0; i < marines.size(); i++) {
            //std::cout << "Mrn stat: " << marines[i].isAlive() << "\n";
            if (marines[i].isAlive() == 0) {
                removeMarines.push_back(i);
            }
        }
        // Reverse vector so largest elements are last
        reverse(removeMarines.begin(), removeMarines.end());
        // Removing marines
        for(int j = 0; j < removeMarines.size(); j++) {
            marines.erase (marines.begin()+removeMarines[j]);
        }
        // Clearing vector
        removeMarines.clear();
        

        // Finding indices to remove
        for(int i = 0; i < splat.size(); i++) {
            //std::cout << "Mrn stat: " << marines[i].isAlive() << "\n";
            if (splat[i].isDead() == 1) {
                removeDead.push_back(i);
            }
        }
        // Reverse vector so largest elements are last
        reverse(removeDead.begin(), removeDead.end());
        // Removing dead
        for(int j = 0; j < removeDead.size(); j++) {
            splat.erase (splat.begin()+removeDead[j]);
        }
        // Clearing vector
        removeDead.clear();


        // Update Screen
        SDL_RenderPresent(renderer);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_duration = frame_end - frame_start;

        if (DEBUG) { // Print out some info every 0.5 seconds
            if (frame_end - title_timestamp >= 1000) {
                std::cout << "***********************************\n";
                std::cout << "     Some debugging information!   \n";
                std::cout << "***********************************\n";
                std::cout << "Number of marines  : " << marines.size() << "\n";
                std::cout << "Number of splat    : " << splat.size() << "\n";
                std::cout << "Frame start (sprz) : " << frame_start << "\n";
            }
        }

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            durationSeconds = durationSeconds + 1;
            UpdateWindowTitle(marineKills, marines.size(), turret.GetHitPoints(), durationSeconds);
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

void Renderer::UpdateWindowTitle(int score, int numMarines, int health, int seconds) {
  std::string title{"!! WarGame !! -- Marines killed: " + std::to_string(score) + ", Number of marines: " + std::to_string(numMarines) + ", Turret Health: " + std::to_string(health) + ", Run Time: " + std::to_string(seconds)};
  SDL_SetWindowTitle(window, title.c_str());
}

void Renderer::PrintGameOver(int score, int seconds) {
    std::cout << "--| GAME OVER |--\n";
    std::cout << "Thanks for playing !! WarGame !!\n\n";
    std::cout << "You killed : " << score << " enemies!\n";
    std::cout << "You lasted : " << seconds << " secpnds.\n\n";
}

int Renderer::GetQuadrant(float rads) {
    // Finds quadrant based on rads
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

std::vector<int> Renderer::RandomPoint() {
    int QUAD, xPos, yPos;

    // Draw a random point on the screen
    // Ensures a uniform distribution, i.e. marines come from all directions
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distrX(-640, 640); // define the range
    std::uniform_int_distribution<> distrY(-420, 420); // define the range

    // Initial values
    xPos = distrX(gen);
    yPos = distrY(gen);

    // Handle edge case
    if (xPos == 0 && yPos == 0) {
        xPos = 1;
        yPos = 1;
    }
    float rads = GetRadians(xPos, yPos);
    QUAD = GetQuadrant(rads);

    // Find point on circle that is 790 from center (just outside screen)
    // Also adjust from (0,0) center to screen reference
    xPos = GetPolarX(rads, 790) + 640;
    yPos = GetPolarY(rads, 790) + 420;

    // Defining vector and returning
    std::vector<int> posVector = {xPos, yPos, QUAD};
    return posVector;
}

int Renderer::GetPolarX(float radians, float dist) {
    return round(dist*cos(radians));
}
int Renderer::GetPolarY(float radians, float dist) {
    return round(dist*sin(radians));
}

float Renderer::GetRadians(int x, int y) {
    return atan2(y, x);
}

float Renderer::GetDist(int x, int y) {
    x = x - 640;
    y = y - 420;
    float dist = sqrt(x*x + y*y);
    return dist;
}

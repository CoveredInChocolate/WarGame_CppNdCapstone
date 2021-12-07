// Experimentation - minimal working examples
/*
make all
./mwe
*/

#include <SDL2/SDL.h>  
#include <iostream>


int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("!! WarGame !!",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 840, 0);
    // Loading and displaying image
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("grass4.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    // Resizing
    SDL_Rect dstrect = { 0, 0, 640, 420 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_Rect dstrect2 = { 640, 0, 640, 420 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    SDL_Rect dstrect3 = { 0, 420, 640, 420 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect3);
    SDL_Rect dstrect4 = { 640, 420, 640, 420 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect4);
    //SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Add trees
    SDL_Surface * tree1 = SDL_LoadBMP("tree1.bmp");
    SDL_Texture * tree1text = SDL_CreateTextureFromSurface(renderer, tree1);
    SDL_Rect t1rect = { 154, 185, 240, 240 };
    SDL_Surface * tree2 = SDL_LoadBMP("tree2.bmp");
    SDL_Texture * tree2text = SDL_CreateTextureFromSurface(renderer, tree2);
    SDL_Rect t2rect = { 825, 94, 240, 240 };
    SDL_Surface * tree3 = SDL_LoadBMP("tree3.bmp");
    SDL_Texture * tree3text = SDL_CreateTextureFromSurface(renderer, tree3);
    SDL_Rect t3rect = { 915, 523, 240, 240 };
    SDL_RenderCopy(renderer, tree1text, NULL, &t1rect);
    SDL_RenderCopy(renderer, tree2text, NULL, &t2rect);
    SDL_RenderCopy(renderer, tree3text, NULL, &t3rect);

    // Debris
    /*
    Requires more work! Hard to make it look natural :)
    SDL_Surface * debris = SDL_LoadBMP("wg_debris.bmp");
    SDL_Texture * debrisText = SDL_CreateTextureFromSurface(renderer, debris);
    SDL_RenderCopy(renderer, debrisText, NULL, NULL);
    */

   // Load in Marine
   int mrnSize = 60;
    SDL_Surface * mrn = SDL_LoadBMP("scmarine.bmp");
    SDL_Texture * mrnText = SDL_CreateTextureFromSurface(renderer, mrn);
    SDL_Rect srcrectMRN_NN = { 0, 0, 29, 30 };
    SDL_Rect dstrectMRN_NN = { 600, 400, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NN, &dstrectMRN_NN);
    SDL_Rect srcrectMRN_NE = { 256, 0, 29, 30 };
    SDL_Rect dstrectMRN_NE = { 640, 440, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NE, &dstrectMRN_NE);
    SDL_Rect srcrectMRN_EE = { 512, 0, 29, 30 };
    SDL_Rect dstrectMRN_EE = { 680, 480, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_EE, &dstrectMRN_EE);
    SDL_Rect srcrectMRN_SE = { 768, 0, 29, 30 };
    SDL_Rect dstrectMRN_SE = { 640, 520, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SE, &dstrectMRN_SE);
    SDL_Rect srcrectMRN_SS = { 1024, 0, 29, 30 };
    SDL_Rect dstrectMRN_SS = { 600, 560, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SS, &dstrectMRN_SS);



    SDL_RenderPresent(renderer);
 
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}

// Next:
// Animating starcraft marine

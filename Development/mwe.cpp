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

    // Load in Marine - will do this in a for loop or with a function :)
    int mrnSize = 60;
    SDL_Surface * mrn = SDL_LoadBMP("scmarine_cut_mirror_shadows.bmp");
    SDL_Texture * mrnText = SDL_CreateTextureFromSurface(renderer, mrn);
    SDL_Rect srcrectMRN_NN = { 0, 0, 29, 35 };
    SDL_Rect dstrectMRN_NN = { 600, 400, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_NE = { 39, 0, 29, 35 };
    SDL_Rect dstrectMRN_NE = { 640, 440, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_EE = { 78, 0, 29, 35 };
    SDL_Rect dstrectMRN_EE = { 680, 480, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_SE = { 117, 0, 29, 35 };
    SDL_Rect dstrectMRN_SE = { 640, 520, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_SS = { 156, 0, 29, 35 };
    SDL_Rect dstrectMRN_SS = { 600, 560, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_SW = { 195, 0, 29, 35 };
    SDL_Rect dstrectMRN_SW = { 560, 520, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_WW = { 234, 0, 29, 35 };
    SDL_Rect dstrectMRN_WW = { 520, 480, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_NW = { 273, 0, 29, 35 };
    SDL_Rect dstrectMRN_NW = { 560, 440, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NN, &dstrectMRN_NN);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NE, &dstrectMRN_NE);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_EE, &dstrectMRN_EE);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NW, &dstrectMRN_NW);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SE, &dstrectMRN_SE);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SS, &dstrectMRN_SS);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SW, &dstrectMRN_SW);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_WW, &dstrectMRN_WW);

    // All walking NW
    SDL_Rect srcrectMRN_1 = { 273, 255+0*64, 29, 35 };
    SDL_Rect dstrectMRN_1 = { 50, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_2 = { 273, 255+1*64, 29, 35 };
    SDL_Rect dstrectMRN_2 = { 100, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_3 = { 273, 255+2*64, 29, 35 };
    SDL_Rect dstrectMRN_3 = { 150, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_4 = { 273, 255+3*64, 29, 35 };
    SDL_Rect dstrectMRN_4 = { 200, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_5 = { 273, 255+4*64, 29, 35 };
    SDL_Rect dstrectMRN_5 = { 250, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_6 = { 273, 255+5*64, 29, 35 };
    SDL_Rect dstrectMRN_6 = { 300, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_7 = { 273, 255+6*64, 29, 35 };
    SDL_Rect dstrectMRN_7 = { 350, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_8 = { 273, 255+7*64, 29, 35 };
    SDL_Rect dstrectMRN_8 = { 400, 680, mrnSize, mrnSize };
    SDL_Rect srcrectMRN_9 = { 273, 255+8*64, 29, 35 };
    SDL_Rect dstrectMRN_9 = { 450, 680, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_1, &dstrectMRN_1);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_2, &dstrectMRN_2);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_3, &dstrectMRN_3);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_4, &dstrectMRN_4);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_5, &dstrectMRN_5);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_6, &dstrectMRN_6);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_7, &dstrectMRN_7);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_8, &dstrectMRN_8);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRN_9, &dstrectMRN_9);

    // Death Animation
    SDL_Rect srcrectMRND_1 = { 0+0*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_1 = { 60, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_2 = { 0+1*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_2 = { 120, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_3 = { 0+2*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_3 = { 180, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_4 = { 0+3*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_4 = { 240, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_5 = { 0+4*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_5 = { 300, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_6 = { 0+5*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_6 = { 360, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_7 = { 0+6*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_7 = { 420, 150, mrnSize, mrnSize };
    SDL_Rect srcrectMRND_8 = { 0+7*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_8 = { 480, 150, mrnSize, mrnSize };
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_1, &dstrectMRND_1);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_2, &dstrectMRND_2);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_3, &dstrectMRND_3);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_4, &dstrectMRND_4);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_5, &dstrectMRND_5);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_6, &dstrectMRND_6);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_7, &dstrectMRND_7);
    SDL_RenderCopy(renderer, mrnText, &srcrectMRND_8, &dstrectMRND_8);

    // All Turret Sprites
    int gunSize = 90;
    SDL_Surface * gg = SDL_LoadBMP("gluegun_anim.bmp");
    SDL_Texture * ggText = SDL_CreateTextureFromSurface(renderer, gg);
    SDL_Rect srcrectGUN_NN = { 0, 0, 80, 75 };
    SDL_Rect dstrectGUN_NN = { 800, 600, gunSize, gunSize };
    SDL_Rect srcrectGUN_NE = { 560, 0, 80, 75 };
    SDL_Rect dstrectGUN_NE = { 800, 500, gunSize, gunSize };
    SDL_Rect srcrectGUN_EE = { 1206, 0, 80, 75 };
    SDL_Rect dstrectGUN_EE = { 800, 400, gunSize, gunSize };
    SDL_Rect srcrectGUN_SE = { 560, 75, 80, 75 };
    SDL_Rect dstrectGUN_SE = { 800, 300, gunSize, gunSize };
    SDL_Rect srcrectGUN_SS = { 1206, 75, 80, 75 };
    SDL_Rect dstrectGUN_SS = { 900, 600, gunSize, gunSize };
    SDL_Rect srcrectGUN_SW = { 560, 148, 80, 75 };
    SDL_Rect dstrectGUN_SW = { 900, 500, gunSize, gunSize };
    SDL_Rect srcrectGUN_WW = { 1196, 150, 80, 75 };
    SDL_Rect dstrectGUN_WW = { 900, 400, gunSize, gunSize };
    SDL_Rect srcrectGUN_NW = { 560, 219, 80, 75 };
    SDL_Rect dstrectGUN_NW = { 900, 300, gunSize, gunSize };
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_NN, &dstrectGUN_NN);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_NE, &dstrectGUN_NE);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_EE, &dstrectGUN_EE);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_SE, &dstrectGUN_SE);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_SS, &dstrectGUN_SS);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_SW, &dstrectGUN_SW);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_WW, &dstrectGUN_WW);
    SDL_RenderCopy(renderer, ggText, &srcrectGUN_NW, &dstrectGUN_NW);

    // Create animation
    SDL_RenderPresent(renderer);

    // Loading muzzle
    //int muzzleSize = 20;
    SDL_Surface * mzImg = SDL_LoadBMP("muzzle_EE.bmp");
    SDL_Texture * mzlText = SDL_CreateTextureFromSurface(renderer, mzImg);
    SDL_Rect srcrectMUZZLE = { 50, 50, 100, 50 };
    SDL_Rect dstrectMUZZLE = { 1000, 100, 70, 35 };
    SDL_RenderCopy(renderer, mzlText, &srcrectMUZZLE, &dstrectMUZZLE);

    SDL_Rect srcrectAN;
    SDL_Rect dstrectAN;
    //SDL_Renderer * rendAnim = SDL_CreateRenderer(window, 1, 0);
    // Test animation
    while (!quit) {
        while (SDL_PollEvent(&event) != NULL) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 150) % 9;
        Uint32 sprite2 = (ticks / 150) % 8;

        //SDL_Rect srcrect = { sprite * 32, 0, 32, 64 };
        //SDL_Rect srcrectAN = { 273, 255 + sprite*64, 29, 35 };
        SDL_Rect srcrectAN = { 268, 255 + sprite*64, 29, 35 };
        SDL_Rect dstrectAN = { 50, 480, mrnSize, mrnSize };
        SDL_Rect srcrectDAN = { 0 + sprite2*60, 830, 60, 35 };
        SDL_Rect dstrectDAN = { 250-sprite2*4, 480, mrnSize, mrnSize };
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect3);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect4);
        SDL_RenderCopy(renderer, tree1text, NULL, &t1rect);
        SDL_RenderCopy(renderer, tree2text, NULL, &t2rect);
        SDL_RenderCopy(renderer, tree3text, NULL, &t3rect);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NN, &dstrectMRN_NN);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NE, &dstrectMRN_NE);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_EE, &dstrectMRN_EE);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_NW, &dstrectMRN_NW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SE, &dstrectMRN_SE);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SS, &dstrectMRN_SS);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_SW, &dstrectMRN_SW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_WW, &dstrectMRN_WW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_1, &dstrectMRN_1);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_2, &dstrectMRN_2);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_3, &dstrectMRN_3);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_4, &dstrectMRN_4);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_5, &dstrectMRN_5);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_6, &dstrectMRN_6);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_7, &dstrectMRN_7);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_8, &dstrectMRN_8);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRN_9, &dstrectMRN_9);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_1, &dstrectMRND_1);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_2, &dstrectMRND_2);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_3, &dstrectMRND_3);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_4, &dstrectMRND_4);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_5, &dstrectMRND_5);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_6, &dstrectMRND_6);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_7, &dstrectMRND_7);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRND_8, &dstrectMRND_8);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN, &dstrectAN);
        SDL_RenderCopy(renderer, mrnText, &srcrectDAN, &dstrectDAN);
        // GUN
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_NN, &dstrectGUN_NN);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_NE, &dstrectGUN_NE);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_EE, &dstrectGUN_EE);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_SE, &dstrectGUN_SE);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_SS, &dstrectGUN_SS);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_SW, &dstrectGUN_SW);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_WW, &dstrectGUN_WW);
        SDL_RenderCopy(renderer, ggText, &srcrectGUN_NW, &dstrectGUN_NW);

        // Turret Muzzle
        SDL_RenderCopy(renderer, mzlText, &srcrectMUZZLE, &dstrectMUZZLE);

        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(tree1text);
    SDL_DestroyTexture(tree2text);
    SDL_DestroyTexture(tree3text);
    SDL_DestroyTexture(mrnText);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// Next:
// Animating starcraft marine

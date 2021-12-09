// Experimentation - minimal working examples
/*
make all
./mwe
*/

#include <SDL2/SDL.h>  
#include <iostream>
#include <cmath>
#include <thread>

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
    SDL_Rect dstrect2 = { 640, 0, 640, 420 };
    SDL_Rect dstrect3 = { 0, 420, 640, 420 };
    SDL_Rect dstrect4 = { 640, 420, 640, 420 };
    //SDL_RenderCopy(renderer, texture, NULL, &dstrect4);
    //SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
    //SDL_RenderCopy(renderer, texture, NULL, &dstrect3);
    //SDL_RenderCopy(renderer, texture, NULL, &dstrect);

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
    //SDL_RenderCopy(renderer, tree1text, NULL, &t1rect);
    //SDL_RenderCopy(renderer, tree2text, NULL, &t2rect);
    //SDL_RenderCopy(renderer, tree3text, NULL, &t3rect);


    // Load in Marine - will do this in a for loop or with a function :)
    int mrnSize = 60;
    float mrnFac = 1.72;
    float mrnFacAtt = 1.9;
    SDL_Surface * mrn = SDL_LoadBMP("scmarine_cut_mirror_shadows.bmp");
    SDL_Texture * mrnText = SDL_CreateTextureFromSurface(renderer, mrn);
    int mrnCOL_NN = 0;
    int mrnCOL_NE = 39;
    int mrnCOL_EE = 78;
    int mrnCOL_SE = 117;
    int mrnCOL_SS = 156;
    int mrnCOL_SW = 195;
    int mrnCOL_WW = 234;
    int mrnCOL_NW = 273;


    // Death Animation
    SDL_Rect srcrectMRND_1 = { 0+0*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_1 = { 50, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_2 = { 0+1*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_2 = { 150, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_3 = { 0+2*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_3 = { 250, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_4 = { 0+3*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_4 = { 350, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_5 = { 0+4*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_5 = { 450, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_6 = { 0+5*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_6 = { 550, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_7 = { 0+6*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_7 = { 650, 150, mrnFac*60, mrnFac*35 };
    SDL_Rect srcrectMRND_8 = { 0+7*60, 830, 60, 35 };
    SDL_Rect dstrectMRND_8 = { 750, 150, mrnFac*60, mrnFac*35 };


    // Attack Animation Frames SE
    //SDL_Rect srcrectMRNA_1 = { 114, 127+0*64, 40, 37 };
    //SDL_Rect dstrectMRNA_1 = { 80, 580, mrnFac*40, mrnFac*37 };
    //SDL_Rect srcrectMRNA_2 = { 114, 127+1*64, 40, 37 };
    //SDL_Rect dstrectMRNA_2 = { 130, 580, mrnFac*40, mrnFac*37 };
    //SDL_RenderCopy(renderer, mrnText, &srcrectMRNA_1, &dstrectMRNA_1);
    //SDL_RenderCopy(renderer, mrnText, &srcrectMRNA_2, &dstrectMRNA_2);

    // All Turret Sprites
    int gunSize = 90;
    SDL_Surface * gg = SDL_LoadBMP("gluegun_anim.bmp");
    SDL_Texture * ggText = SDL_CreateTextureFromSurface(renderer, gg);

    // Game Over
    float explosionSize = 0.6;
    SDL_Surface * govr = SDL_LoadBMP("GameOver.bmp");
    SDL_Texture * goverText = SDL_CreateTextureFromSurface(renderer, govr);
    SDL_Rect srcrectGover = { 5, 5, 390, 320 };
    SDL_Rect dstrectGover = { 950, 50, explosionSize*321, explosionSize*385 };
    SDL_RenderCopy(renderer, goverText, &srcrectGover, &dstrectGover);

    // Create animation
    SDL_RenderPresent(renderer);

    // Loading muzzle
    float muzzleSizeFactor = 0.7;
    SDL_Surface * mzImgEE = SDL_LoadBMP("muzzle_EE.bmp");
    SDL_Surface * mzImgNE = SDL_LoadBMP("muzzle_NE.bmp");
    SDL_Surface * mzImgNN = SDL_LoadBMP("muzzle_NN.bmp");
    SDL_Surface * mzImgNW = SDL_LoadBMP("muzzle_NW.bmp");
    SDL_Surface * mzImgSE = SDL_LoadBMP("muzzle_SE.bmp");
    SDL_Surface * mzImgSS = SDL_LoadBMP("muzzle_SS.bmp");
    SDL_Surface * mzImgSW = SDL_LoadBMP("muzzle_SW.bmp");
    SDL_Surface * mzImgWW = SDL_LoadBMP("muzzle_WW.bmp");
 

    SDL_Rect srcrectAN;
    SDL_Rect dstrectAN;

    // Animated gun
    SDL_Rect srcrectGUNAN = { 0, 0, 80, 75 };
    SDL_Rect dstrectGUNAN = { 600, 398, gunSize, gunSize };
    // Animated muzzle
    SDL_Texture * mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgNN);
    SDL_Rect srectMuzzle = { 45, 55, 58, 100 };
    SDL_Rect dtrectMuzzle = { 1000, 300, muzzleSizeFactor*58, muzzleSizeFactor*100 };

    
    // Test animation
    int xxx, xxy;
    // Correcting so central point of screen is (0,0)
    int xcorr, ycorr;
    Uint32 buttons;
    // Quadrant variable
    std::string QUADRANT = "XX";
    int QUAD = 0;


    // Definitions
    Uint32 ticks = 0;
    Uint32 sprite = 0;
    Uint32 sprite2 = 0;
    Uint32 mzlSprite = 0;
    Uint32 mrnAttackSprite = 0;

    // Marine - Walk animation NE
    SDL_Rect srcrectAN_NE = { mrnCOL_NE, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_NE = { 50, 480, mrnSize, mrnSize };
    // Marine - Walk animation WW
    SDL_Rect srcrectAN_WW = { mrnCOL_WW, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_WW = { 50, 420, mrnSize, mrnSize };
    // Marine - Walk animation SE
    SDL_Rect srcrectAN_SE = { mrnCOL_SE, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_SE = { 50, 360, mrnSize, mrnSize };
    // Marine - Walk animation SS
    SDL_Rect srcrectAN_SS = { mrnCOL_SS, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_SS = { 50, 300, mrnSize, mrnSize };
    // Marine - Walk animation SW
    SDL_Rect srcrectAN_SW = { mrnCOL_SW, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_SW = { 150, 480, mrnSize, mrnSize };
    // Marine - Walk animation EE
    SDL_Rect srcrectAN_EE = { mrnCOL_EE, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_EE = { 150, 420, mrnSize, mrnSize };
    // Marine - Walk animation NN
    SDL_Rect srcrectAN_NN = { mrnCOL_NN, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_NN = { 150, 360, mrnSize, mrnSize };
    // Marine - Walk animation NW
    SDL_Rect srcrectAN_NW = { mrnCOL_NW, 255 + sprite*64, 29, 35 };
    SDL_Rect dstrectAN_NW = { 150, 300, mrnSize, mrnSize };
    // Marine - Death animation
    SDL_Rect srcrectDAN = { 0 + sprite2*60, 830, 60, 35 };
    SDL_Rect dstrectDAN = { 250-sprite2*7, 480, mrnFac*60, mrnFac*35 };
    // Marine - Attack animation SE
    SDL_Rect srcrectMRNAtt_SE = { mrnCOL_SE, 127 + mrnAttackSprite*64, 40, 37 };
    SDL_Rect dstrectMRNAtt_SE = { 200, 580, mrnFacAtt*40, mrnFacAtt*37 };
    // Marine - Attack animation SS
    SDL_Rect srcrectMRNAtt_SS = { mrnCOL_SS, 127 + mrnAttackSprite*64, 40, 37 };
    SDL_Rect dstrectMRNAtt_SS = { 260, 580, mrnFacAtt*40, mrnFacAtt*37 };
    // Marine - Attack animation SW
    SDL_Rect srcrectMRNAtt_SW;
    SDL_Rect dstrectMRNAtt_SW; 
    // Marine - Attack animation NW
    SDL_Rect srcrectMRNAtt_NW = { mrnCOL_NW-5, 127 + mrnAttackSprite*64, 40, 37 };
    SDL_Rect dstrectMRNAtt_NW = { 320, 580, mrnFacAtt*40, mrnFacAtt*37 };
    SDL_Rect srcrectMRNAtt_WW;
    SDL_Rect dstrectMRNAtt_WW; 
    SDL_Rect srcrectMRNAtt_EE;
    SDL_Rect dstrectMRNAtt_EE; 
    SDL_Rect srcrectMRNAtt_NE;
    SDL_Rect dstrectMRNAtt_NE; 
    SDL_Rect srcrectMRNAtt_NN;
    SDL_Rect dstrectMRNAtt_NN; 


    SDL_PumpEvents();  // make sure we have the latest mouse state.
    buttons = SDL_GetMouseState(&xxx, &xxy);
    // #########################################################################################################
    // ########################################################################################### GAME LOOP
    // #########################################################################################################
    while (!quit) {
        while (SDL_PollEvent(&event) != NULL) {

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        // Change cursor - Low priority
        //SDL_ShowCursor( SDL_DISABLE );

        // Animation controls
        ticks = SDL_GetTicks();
        sprite = (ticks / 150) % 9;
        sprite2 = (ticks / 150) % 8;
        mzlSprite = (ticks / 50) % 2;
        mrnAttackSprite = (ticks / 150) % 2;

        // Reduce CPU load
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // Mouse stats
        SDL_PumpEvents();  // make sure we have the latest mouse state.
        buttons = SDL_GetMouseState(&xxx, &xxy);
        
        // Calculating corrected points: (0,0) in the center
        xcorr = xxx - 1280/2;
        ycorr = xxy - 840/2;

        // Polar coordinates, more specifically: radians
        float rads = atan2(ycorr, xcorr);

        //SDL_Log("Mouse cursor is at %d, %d", xcorr, ycorr);
        //SDL_Log("Mouse cursor is at %f radians", rads);

        // Define quadrants
        if (rads > 7*M_PI/8 || rads < -7*M_PI/8) {
            //SDL_Log("Quadrant WW");
            QUADRANT = "WW";
            QUAD = 1;
        } else if (rads < -M_PI/8 && rads > -3*M_PI/8) {
            //SDL_Log("Quadrant NE");
            QUADRANT = "NE";
            QUAD = 2;
        } else if (rads < -3*M_PI/8 && rads > -5*M_PI/8) {
            //SDL_Log("Quadrant NN");
            QUADRANT = "NN";
            QUAD = 3;
        } else if (rads < -5*M_PI/8 && rads > -7*M_PI/8) {
            //SDL_Log("Quadrant NW");
            QUADRANT = "NW";
            QUAD = 4;
        } else if (rads < M_PI/8 && rads > -M_PI/8) {
            //SDL_Log("Quadrant EE");
            QUADRANT = "EE";
            QUAD = 5;
        } else if(rads > M_PI/8 && rads < 3*M_PI/8) {
            //SDL_Log("Quadrant SE");
            QUADRANT = "SE";
            QUAD = 6;
        } else if(rads > 3*M_PI/8 && rads < 5*M_PI/8) {
            //SDL_Log("Quadrant SS");
            QUADRANT = "SS";
            QUAD = 7;
        } else if(rads > 5*M_PI/8 && rads < 7*M_PI/8) {
            //SDL_Log("Quadrant SW");
            QUADRANT = "SW";
            QUAD = 8;
        } else {
            SDL_Log("Quadrant XX");
        }

        // ################## CLEAR RENDER
        SDL_RenderClear(renderer);

        // Animated GUN & MUZZLE
        switch (QUAD) {
        case 1:
            // WW
            srcrectGUNAN = { 1196, 150, 80, 75 };
            dstrectGUNAN = { 600-2, 398+7, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgWW);
            srectMuzzle = { 57, 61, mzlSprite*98, mzlSprite*51 };
            dtrectMuzzle = { 530, 420, muzzleSizeFactor*98, muzzleSizeFactor*51 };
            break;
        case 2:
            // NE
            srcrectGUNAN = { 560, 0, 80, 75 };
            dstrectGUNAN = { 600, 398, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgNE);
            srectMuzzle = { 83, 88, mzlSprite*78, mzlSprite*73 };
            dtrectMuzzle = { 665, 350, muzzleSizeFactor*78, muzzleSizeFactor*73 };
            break;
        case 3:
            // NN
            srcrectGUNAN = { 0, 0, 80, 75 };
            dstrectGUNAN = { 600, 398, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgNN);
            srectMuzzle = { 45, 55, mzlSprite*58, mzlSprite*100 };
            dtrectMuzzle = { 628, 325, muzzleSizeFactor*58, muzzleSizeFactor*100 };
            break;
        case 4:
            // NW
            srcrectGUNAN = { 560, 219, 80, 75 };
            dstrectGUNAN = { 600, 398-2, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgNW);
            srectMuzzle = { 86, 96, mzlSprite*79, mzlSprite*79 };
            dtrectMuzzle = { 560, 350, muzzleSizeFactor*79, muzzleSizeFactor*79 };
            break;
        case 5:
            // EE
            srcrectGUNAN = { 1206, 0, 80, 75 };
            dstrectGUNAN = { 600+3, 398, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgEE);
            srectMuzzle = { mzlSprite*50, mzlSprite*50, mzlSprite*100, mzlSprite*50 };
            dtrectMuzzle = { 705, 420, muzzleSizeFactor*100, muzzleSizeFactor*50 };
            break;
        case 6:
            // SE
            srcrectGUNAN = { 560, 75, 80, 75 };
            dstrectGUNAN = { 600, 398+3, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgSE);
            srectMuzzle = { mzlSprite*90, mzlSprite*80, mzlSprite*82, mzlSprite*80 };
            dtrectMuzzle = { 680, 460, muzzleSizeFactor*82, muzzleSizeFactor*80 };
            break;
        case 7:
            // SS
            srcrectGUNAN = { 1206, 75, 80, 75 };
            dstrectGUNAN = { 600+3, 398+3, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgSS);
            srectMuzzle = { mzlSprite*60, mzlSprite*50, mzlSprite*56, mzlSprite*92 };
            dtrectMuzzle = { 628, 480, muzzleSizeFactor*56, muzzleSizeFactor*92 };
            break;
        case 8:
            // SW
            srcrectGUNAN = { 560, 148, 80, 75 };
            dstrectGUNAN = { 600, 398+5, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgSW);
            srectMuzzle = { mzlSprite*94, mzlSprite*88, mzlSprite*82, mzlSprite*81 };
            dtrectMuzzle = { 560, 460, muzzleSizeFactor*82, muzzleSizeFactor*81 };
            break;
        default:
            // Defaults to NN
            srcrectGUNAN = { 0, 0, 80, 75 };
            dstrectGUNAN = { 600, 398, gunSize, gunSize };
            mzlAN = SDL_CreateTextureFromSurface(renderer, mzImgNN);
            srectMuzzle = { mzlSprite*45, mzlSprite*55, mzlSprite*58, mzlSprite*100 };
            dtrectMuzzle = { 628, 320, muzzleSizeFactor*58, muzzleSizeFactor*100 };
        }

        

        // Marine - Walk animation NE
        srcrectAN_NE = { mrnCOL_NE, 255 + sprite*64, 29, 35 };
        dstrectAN_NE = { 50, 480, mrnSize, mrnSize };
        // Marine - Walk animation WW
        srcrectAN_WW = { mrnCOL_WW, 255 + sprite*64, 29, 35 };
        dstrectAN_WW = { 50, 420, mrnSize, mrnSize };
        // Marine - Walk animation SE
        srcrectAN_SE = { mrnCOL_SE, 255 + sprite*64, 29, 35 };
        dstrectAN_SE = { 50, 360, mrnSize, mrnSize };
        // Marine - Walk animation SS
        srcrectAN_SS = { mrnCOL_SS, 255 + sprite*64, 29, 35 };
        dstrectAN_SS = { 50, 300, mrnSize, mrnSize };
        // Marine - Walk animation SW
        srcrectAN_SW = { mrnCOL_SW, 255 + sprite*64, 29, 35 };
        dstrectAN_SW = { 150, 480, mrnSize, mrnSize };
        // Marine - Walk animation EE
        srcrectAN_EE = { mrnCOL_EE, 255 + sprite*64, 29, 35 };
        dstrectAN_EE = { 150, 420, mrnSize, mrnSize };
        // Marine - Walk animation NN
        srcrectAN_NN = { mrnCOL_NN, 255 + sprite*64, 29, 35 };
        dstrectAN_NN = { 150, 360, mrnSize, mrnSize };
        // Marine - Walk animation NW
        srcrectAN_NW = { mrnCOL_NW, 255 + sprite*64, 29, 35 };
        dstrectAN_NW = { 150, 300, mrnSize, mrnSize };
        // Marine - Death animation
        srcrectDAN = { 0 + sprite2*60, 830, 60, 35 };
        dstrectDAN = { 250-sprite2*7, 480, mrnFac*60, mrnFac*35 };
        // Marine - Attack animation NW
        srcrectMRNAtt_SW = { mrnCOL_SW-8, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_SW = { 100, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation SE
        srcrectMRNAtt_SE = { mrnCOL_SE, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_SE = { 200, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation SS
        srcrectMRNAtt_SS = { mrnCOL_SS-8, 127 + mrnAttackSprite*64, 35, 37 };
        dstrectMRNAtt_SS = { 300, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation NW
        srcrectMRNAtt_NW = { mrnCOL_NW-5, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_NW = { 400, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // --------------------------------------------
        // Marine - Attack animation WW
        srcrectMRNAtt_WW = { mrnCOL_WW-10, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_WW = { 100, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation NE
        srcrectMRNAtt_NE = { mrnCOL_NE, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_NE = { 200, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation EE
        srcrectMRNAtt_EE = { mrnCOL_EE, 127 + mrnAttackSprite*64, 35, 37 };
        dstrectMRNAtt_EE = { 300, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // Marine - Attack animation NN
        srcrectMRNAtt_NN = { mrnCOL_NN, 127 + mrnAttackSprite*64, 40, 37 };
        dstrectMRNAtt_NN = { 400, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // GRASS
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect2);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect3);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect4);
        // TREES
        SDL_RenderCopy(renderer, tree1text, NULL, &t1rect);
        SDL_RenderCopy(renderer, tree2text, NULL, &t2rect);
        SDL_RenderCopy(renderer, tree3text, NULL, &t3rect);

        // Render user controlled GUN and animated Muzzle
        SDL_RenderCopy(renderer, ggText, &srcrectGUNAN, &dstrectGUNAN);
        if ((buttons & SDL_BUTTON_LMASK) != 0) {
            //SDL_Log("Mouse Button 1 (left) is pressed.");
            SDL_RenderCopy(renderer, mzlAN, &srectMuzzle, &dtrectMuzzle);
        }

        // WALKING ANIMATIONS
        /*
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_NE, &dstrectAN_NE);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_WW, &dstrectAN_WW);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_SE, &dstrectAN_SE);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_SS, &dstrectAN_SS);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_SW, &dstrectAN_SW);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_EE, &dstrectAN_EE);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_NW, &dstrectAN_NW);
        SDL_RenderCopy(renderer, mrnText, &srcrectAN_NN, &dstrectAN_NN);
        */
        /*
        // ATTACKING ANIMATIONS
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_SE, &dstrectMRNAtt_SE);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_SS, &dstrectMRNAtt_SS);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_SW, &dstrectMRNAtt_SW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_NW, &dstrectMRNAtt_NW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_WW, &dstrectMRNAtt_WW);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_EE, &dstrectMRNAtt_EE);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_NN, &dstrectMRNAtt_NN);
        SDL_RenderCopy(renderer, mrnText, &srcrectMRNAtt_NE, &dstrectMRNAtt_NE);
        */
        //SDL_RenderCopy(renderer, mrnText, &srcrectDAN, &dstrectDAN); // DEATH


        // GAME OVER EXPLOSION Over
        //SDL_RenderCopy(renderer, goverText, &srcrectGover, &dstrectGover);


        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        // calculates to 30 fps
        SDL_Delay(1000 / 60);
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


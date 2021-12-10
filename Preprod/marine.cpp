#include "renderer.h"
#include "marine.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 

Marine::Marine(int posX, int posY, int quad, float speed) : posX(posX), posY(posY), quad(quad), speed(speed) {
    startX = posX;
    startY = posY;
    SetColumn(quad);
}

void Marine::setTimeOfDeath(int tm) {
    timeOfDeath = tm;
}

void Marine::setSpawnTime(int tm) {
    spawnTime = tm;
}

void Marine::UpdatePosition(int tm) {
    // Moving towards center: 640, 420
    // Attacking after 8 seconds and distance of 200
    if(!attacking) {
        tm = std::min(tm, 8000);
        float timeSinceSpawn = tm - spawnTime;
        float totalTravel = 8000 - spawnTime;
        float propTraveled = timeSinceSpawn/totalTravel;
        //std::cout << "Prop: " << propTraveled << "\n";
        posX = round(640*propTraveled + startX*(1-propTraveled));
        posY = round(420*propTraveled + startY*(1-propTraveled));
        if (GetDist(posX, posY) <= 200) {
            attacking = true;
        }
    }

}

std::vector<int> Marine::GetTextureSource(Uint32 ticks) {
    Uint32 sprite;
    std::vector<int> src;
    if (!attacking) {
        sprite = ((ticks - spawnTime) / 190) % 8;
        src = { mrnCOL, 255 + sprite*64, 29, 35};
    } else {
        sprite = ((ticks - spawnTime) / 150) % 2;
        src = { mrnCOL-attackAdjust, 127 + sprite*64, 40, 37};
    }
    return src;
}

std::vector<int> Marine::GetTextureDestination() {
    std::vector<int> dst = {posX, posY, mrnSize, mrnSize};
    return dst;
}

std::vector<int> Marine::GetDeathSource(Uint32 ticks) {
    Uint32 sprite = ((ticks - timeOfDeath) / 190) % 8;
    if (sprite == 7) {
        setDeadTrue();
    }
    std::vector<int> src =  { 0+sprite*60, 830, 60, 35 };
    return src;
}

std::vector<int> Marine::GetDeathDestination(Uint32 ticks) {
    Uint32 sprite = ((ticks - timeOfDeath) / 190) % 8;
    std::vector<int> dst = {posX-sprite*7, posY, mrnFac*60, mrnFac*35};
    return dst;
}

std::vector<int> Marine::GetPosition() {
    std::vector<int> pos = {posX, posY};
    return pos;
}

bool Marine::isAlive() {
    return alive;
}

bool Marine::isDead() {
    return dead;
}

void Marine::setAliveFalse() {
    // Marine is hit, to play death animation
    alive = false;
}

void Marine::setDeadTrue() {
    // Death animation completed
    dead = true;
}

float Marine::GetDist(int x, int y) {
    x = x - 640;
    y = y - 420;
    float dist = sqrt(x*x + y*y);
    return dist;
}

// void Marine::SetColumn(int quad) {
//     if (quad == 1) {
//         // WW
//         mrnCOL = 78;
//     } else if (quad == 2) {
//         // NW
//         mrnCOL = 117;
//     } else if (quad == 3) {
//         // NN
//         mrnCOL = 156;
//     } else if (quad == 4) {
//         // NE
//         mrnCOL = 195;
//     } else if (quad == 5) {
//         // EE
//         mrnCOL = 234;
//     } else if (quad == 6) {
//         // SE
//         mrnCOL = 273;
//     } else if (quad == 7) {
//         // SS
//         mrnCOL = 0;
//     } else if (quad == 8) {
//         // SW
//         mrnCOL = 39;
//     }
// }

void Marine::SetColumn(int quad) {
    if (quad == 1) {
        // WW
        mrnCOL = 78;
        attackAdjust = 0;
    } else if (quad == 2) {
        // NW
        mrnCOL = 117;
        attackAdjust = 0;
    } else if (quad == 3) {
        // NN
        mrnCOL = 156;
        attackAdjust = 8;
    } else if (quad == 4) {
        // NE
        mrnCOL = 195;
        attackAdjust = 8;
    } else if (quad == 5) {
        // EE
        mrnCOL = 234;
        attackAdjust = 10;
    } else if (quad == 6) {
        // SE
        mrnCOL = 273;
        attackAdjust = 5;
    } else if (quad == 7) {
        // SS
        mrnCOL = 0;
        attackAdjust = 0;
    } else if (quad == 8) {
        // SW
        mrnCOL = 39;
        attackAdjust = 0;
    }
}

        // // Marine - Attack animation NW
        // srcrectMRNAtt_SW = { mrnCOL_SW-8, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_SW = { 100, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation SE
        // srcrectMRNAtt_SE = { mrnCOL_SE, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_SE = { 200, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation SS
        // srcrectMRNAtt_SS = { mrnCOL_SS-8, 127 + mrnAttackSprite*64, 35, 37 };
        // dstrectMRNAtt_SS = { 300, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation NW
        // srcrectMRNAtt_NW = { mrnCOL_NW-5, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_NW = { 400, 580, mrnFacAtt*40, mrnFacAtt*37 };
        // // --------------------------------------------
        // // Marine - Attack animation WW
        // srcrectMRNAtt_WW = { mrnCOL_WW-10, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_WW = { 100, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation NE
        // srcrectMRNAtt_NE = { mrnCOL_NE, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_NE = { 200, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation EE
        // srcrectMRNAtt_EE = { mrnCOL_EE, 127 + mrnAttackSprite*64, 35, 37 };
        // dstrectMRNAtt_EE = { 300, 680, mrnFacAtt*40, mrnFacAtt*37 };
        // // Marine - Attack animation NN
        // srcrectMRNAtt_NN = { mrnCOL_NN, 127 + mrnAttackSprite*64, 40, 37 };
        // dstrectMRNAtt_NN = { 400, 680, mrnFacAtt*40, mrnFacAtt*37 };
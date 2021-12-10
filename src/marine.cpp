#include "renderer.h"
#include "marine.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 

Marine::Marine(int posX, int posY, int quad) : posX(posX), posY(posY), quad(quad) {
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
        int timeSinceSpawn = tm - spawnTime;
        timeSinceSpawn = std::min(timeSinceSpawn, 8000);
        float totalTravel = 8000;
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

bool Marine::isAttacking() {
    return attacking;
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

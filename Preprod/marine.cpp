#include "renderer.h"
#include "marine.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 

Marine::Marine(int posX, int posY, float speed) : posX(posX), posY(posY), speed(speed) {
}

std::vector<int> Marine::GetTextureSource(int QUAD) {
    std::vector<int> src =  {117, 0, 29, 35 };
    return src;
}

std::vector<int> Marine::GetTextureDestination() {
    std::vector<int> dst = {posX, posY, mrnSize, mrnSize};
    return dst;
}

std::vector<int> Marine::GetDeathSource(Uint32 ticks) {
    Uint32 sprite = (ticks / 190) % 8;
    if (sprite == 7) {
        setDeadTrue();
    }
    std::vector<int> src =  { 0+sprite*60, 830, 60, 35 };
    return src;
}

std::vector<int> Marine::GetDeathDestination(Uint32 ticks) {
    Uint32 sprite = (ticks / 190) % 8;
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
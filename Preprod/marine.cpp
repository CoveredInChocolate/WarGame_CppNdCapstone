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
std::vector<int> Marine::GetPosition() {
    std::vector<int> pos = {posX, posY};
    return pos;
}
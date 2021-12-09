#include "renderer.h"
#include "turret.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h> 

Turret::Turret(int hitPoints, int gunSize, float muzzleSizeFactor) :
               hitPoints(hitPoints), gunSize(gunSize), muzzleSizeFactor(muzzleSizeFactor) {
}

int Turret::GetHitPoints() {
    return hitPoints;
}

int Turret::GetGunSize() {
    return gunSize;
}

std::vector<int> Turret::GetTextureSource(int QUAD) {
    switch (QUAD) {
    case 1:
        // WW
        srcCoords = {1196, 150, 80, 75};
        break;
    case 2:
        // NW
        srcCoords = {560, 219, 80, 75};
        break;
    case 3:
        // NN
        srcCoords = {0, 0, 80, 75};
        break;
    case 4:
        // NE
        srcCoords = {560, 0, 80, 75};
        break;
    case 5:
        // EE
        srcCoords = {1206, 0, 80, 75};
        break;
    case 6:
        // SE
        srcCoords = {560, 75, 80, 75};
        break;
    case 7:
        // SS
        srcCoords = {1206, 75, 80, 75};
        break;
    case 8:
        // SW
        srcCoords = {560, 148, 80, 75};
        break;
    }
    return srcCoords;
}

std::vector<int> Turret::GetTextureDestination(int QUAD) {
    switch (QUAD) {
    case 1:
        // WW
        dstCoords = {598, 405, gunSize, gunSize};
        break;
    case 2:
        // NW
        dstCoords = {600, 396, gunSize, gunSize};
        break;
    case 3:
        // NN
        dstCoords = {600, 398, gunSize, gunSize};
        break;
    case 4:
        // NE
        dstCoords = {600, 398, gunSize, gunSize};
        break;
    case 5:
        // EE
        dstCoords = {603, 398, gunSize, gunSize};
        break;
    case 6:
        // SE
        dstCoords = {600, 401, gunSize, gunSize};
        break;
    case 7:
        // SS
        dstCoords = {603, 401, gunSize, gunSize};
        break;
    case 8:
        // SW
        dstCoords = {600, 403, gunSize, gunSize};
        break;
    }
    return dstCoords;
}


std::vector<int> Turret::GetMuzzleSource(int QUAD) {
    switch (QUAD) {
    case 1:
        // WW
        srcCoords = {57, 61, 98, 51};
        break;
    case 2:
        // NW
        srcCoords = {86, 96, 79, 79};
        break;
    case 3:
        // NN
        srcCoords = {45, 55, 58, 100};
        break;
    case 4:
        // NE
        srcCoords = {83, 88, 78, 73};
        break;
    case 5:
        // EE
        srcCoords = {50, 50, 100, 50};
        break;
    case 6:
        // SE
        srcCoords = {90, 80, 82, 80};
        break;
    case 7:
        // SS
        srcCoords = {60, 50, 56, 92};
        break;
    case 8:
        // SW
        srcCoords = {94, 88, 82, 81};
        break;
    }
    return srcCoords;
}


std::vector<int> Turret::GetMuzzleDestination(int QUAD) {
    switch (QUAD) {
    case 1:
        // WW
        dstCoords = {530, 420, muzzleSizeFactor*98, muzzleSizeFactor*51};
        break;
    case 2:
        // NW
        dstCoords = {560, 350, muzzleSizeFactor*79, muzzleSizeFactor*79};
        break;
    case 3:
        // NN
        dstCoords = {628, 325, muzzleSizeFactor*58, muzzleSizeFactor*100};
        break;
    case 4:
        // NE
        dstCoords = {665, 350, muzzleSizeFactor*78, muzzleSizeFactor*73};
        break;
    case 5:
        // EE
        dstCoords = {705, 420, muzzleSizeFactor*100, muzzleSizeFactor*50};
        break;
    case 6:
        // SE
        dstCoords = {680, 460, muzzleSizeFactor*82, muzzleSizeFactor*80};
        break;
    case 7:
        // SS
        dstCoords = {628, 480, muzzleSizeFactor*56, muzzleSizeFactor*92};
        break;
    case 8:
        // SW
        dstCoords = {560, 460, muzzleSizeFactor*82, muzzleSizeFactor*81};
        break;
    }
    return dstCoords;
}

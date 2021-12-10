#ifndef TURRET_H
#define TURRET_H

#include <vector>
#include <SDL2/SDL.h>

class Turret {
 public:
  Turret(int hitPoints, int gunSize, float muzzleSizeFactor);

  int GetHitPoints();
  void SetHitPoints(int attackingMarines);
  int GetGunSize();
  std::vector<int> GetTextureSource(int QUAD); 
  std::vector<int> GetTextureDestination(int QUAD); 
  std::vector<int> GetMuzzleSource(int QUAD); 
  std::vector<int> GetMuzzleDestination(int QUAD); 
  std::vector<int> srcCoords;
  std::vector<int> dstCoords;

 private:
  int hitPoints;
  int gunSize;
  float muzzleSizeFactor;
};

#endif
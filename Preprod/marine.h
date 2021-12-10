#ifndef MARINE_H
#define MARINE_H

#include <vector>
#include <SDL2/SDL.h>

class Marine {
public:
    Marine(int posX, int posY, int quad, float speed);

    std::vector<int> GetTextureSource(Uint32 ticks); 
    std::vector<int> GetTextureDestination(); 
    std::vector<int> GetPosition();
    std::vector<int> GetDeathSource(Uint32 ticks);
    std::vector<int> GetDeathDestination(Uint32 ticks);
    bool isAlive();
    bool isDead();
    void setAliveFalse();
    void setDeadTrue();
    void setTimeOfDeath(int tm);
    void setSpawnTime(int tm);
    void UpdatePosition(int tm);
    float GetDist(int x, int y);
    void SetColumn(int quad);
    int startX;
    int startY;
    int mrnCOL;
    int attackAdjust;

 private:
    float speed;
    int mrnSize{60};
    float mrnFac{1.72};
    float mrnFacAtt{1.9};
    float distance;
    int timeOfDeath{0};
    int spawnTime{0};
    bool alive{true};
    bool dead{false};
    bool attacking{false};
    int posX;
    int posY;
    int quad; // Which quadrant they come FROM, which determines direction
  // Starting point x, y
  // bool attacking;
};

#endif
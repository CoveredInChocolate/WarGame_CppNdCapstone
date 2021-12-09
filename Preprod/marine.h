#ifndef MARINE_H
#define MARINE_H

#include <vector>
#include <SDL2/SDL.h>

class Marine {
public:
    Marine(int posX, int posY, float speed);

    std::vector<int> GetTextureSource(int QUAD); 
    std::vector<int> GetTextureDestination(); 
    std::vector<int> GetPosition(); 

 private:
    float speed;
    int mrnSize{60};
    float mrnFac{1.72};
    float mrnFacAtt{1.9};
    bool alive{true};
    int posX;
    int posY;
  // Starting point x, y
  // Ending point x, y
  // bool attacking;
  // Animation shift
};

#endif
#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"

enum MyColor {
    red, green
};

class Particle {
public: 
    Vector2 position;
    Vector2 velocity;
    MyColor color;

    Particle(float x, float y, MyColor color = red); 
    void randomWalk();
    void update();
};

#endif // PARTICLE_H
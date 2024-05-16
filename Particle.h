#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "PositionedObject.h"

enum MyColor {
    red, green
};

class Particle : public PositionedObject {
public: 
    Vector2 position;
    Vector2 velocity;
    MyColor color;

    Particle(float x, float y, MyColor color = red); 
    void randomWalk();
    void update();
    Vector2 getPosition() override;
};

#endif // PARTICLE_H
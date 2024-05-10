#include "Particle.h"
#include <random>   

Particle::Particle(float x, float y, MyColor color) : position({x, y}), color(color) {} 

void Particle::randomWalk() {
    float speed = 2.0f; 
    velocity.x = (GetRandomValue(-100, 100) / 100.0f) * speed;
    velocity.y = (GetRandomValue(-100, 100) / 100.0f) * speed;
}

void Particle::update() {
    position.x += velocity.x;
    position.y += velocity.y;
}

Vector2 Particle::getPosition() { return position; }
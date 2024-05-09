#ifndef QUADTREE_H
#define QUADTREE_H

#include "raylib.h"
#include <vector>
#include "Particle.h" // Include Particle header

class Quadtree {
public: 
    Rectangle bounds; 
    int capacity = 4;  // Max particles per node
    std::vector<Particle*> particles;  
    bool divided = false;
    Quadtree* northwest;
    Quadtree* northeast;
    Quadtree* southwest;
    Quadtree* southeast;

    Quadtree(Rectangle bounds);
    bool insert(Particle* p);
    void subdivide();
    void query(Rectangle range, std::vector<Particle*>& result);
    void clear();
};

#endif // QUADTREE_H
#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "raylib.h" // Remove if not needed in your new project
#include <vector>
#include "PositionedObject.h"

template <typename T>               //, typename = std::enable_if_t<std::is_base_of<PositionedObject, T>::value>
class Quadtree {
public:
    Rectangle bounds;
    int capacity = 4;
    std::vector<T*> objects;  // Changed type to T*
    bool divided = false;
    Quadtree* northwest;
    Quadtree* northeast;
    Quadtree* southwest;
    Quadtree* southeast;

    Quadtree(Rectangle bounds);
    bool insert(T* object);
    void subdivide();
    void query(Rectangle range, std::vector<T*>& result, 
                bool (*collisionCheckFunc)(const T&, const Rectangle&)); // Added collision check function pointer
    void clear();
    void debugDraw(Color);
};

#include "Quadtree.cpp"

#endif // QUADTREE_HPP
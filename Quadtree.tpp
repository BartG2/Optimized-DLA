#include "Quadtree.hpp"

template <typename T>
Quadtree<T>::Quadtree(Rectangle bounds) : bounds(bounds) {}

template <typename T>
bool Quadtree<T>::insert(T* object) {
    if (!CheckCollisionPointRec(object->getPosition(), bounds)) { // Assuming getPosition() exists for type T
        return false;
    }

    if (objects.size() < capacity) {
        objects.push_back(object);
        return true;
    }

    if (!divided) {
        subdivide();
    }

    // Try inserting into sub-quadrants
    if (northwest->insert(object)) return true;
    if (northeast->insert(object)) return true;
    if (southwest->insert(object)) return true;
    if (southeast->insert(object)) return true;

    return false;
}

template <typename T>
void Quadtree<T>::subdivide() {
    float halfWidth = bounds.width / 2;
    float halfHeight = bounds.height / 2;
    float x = bounds.x;
    float y = bounds.y;

    northwest = new Quadtree({x, y, halfWidth, halfHeight});
    northeast = new Quadtree({x + halfWidth, y, halfWidth, halfHeight});
    southwest = new Quadtree({x, y + halfHeight, halfWidth, halfHeight});
    southeast = new Quadtree({x + halfWidth, y + halfHeight, halfWidth, halfHeight});

    divided = true;
}

template <typename T>
void Quadtree<T>::query(Rectangle range, std::vector<T*>& result, bool (*collisionCheckFunc)(const T&, const Rectangle&)) {
    if (!CheckCollisionRecs(range, bounds)) {
        return;
    }

    for (auto object : objects) {
        if (collisionCheckFunc(*object, range)) { // Use provided collision check function
            result.push_back(object);
        }
    }

    if (divided) {
        northwest->query(range, result, collisionCheckFunc);
        northeast->query(range, result, collisionCheckFunc);
        southwest->query(range, result, collisionCheckFunc);
        southeast->query(range, result, collisionCheckFunc);
    }
}

template <typename T>
void Quadtree<T>::clear() {
    objects.clear();
    divided = false;

    if (northwest) {
        delete northwest;
        northwest = nullptr;
    }
    if (northeast) {
        delete northeast;
        northeast = nullptr;
    }
    if (southwest) {
        delete southwest;
        southwest = nullptr;
    }
    if (southeast) {
        delete southeast;
        southeast = nullptr;
    }
}

template <typename T>
void Quadtree<T>::debugDraw(Color color) {
    //DrawRectangleRec(bounds, Fade(color, 0.2f));  // Draw bounding box
    DrawRectangleLinesEx(bounds, 0.5, color);

    if (divided) {
        northwest->debugDraw(color);
        northeast->debugDraw(color);
        southwest->debugDraw(color);
        southeast->debugDraw(color);
    }
}
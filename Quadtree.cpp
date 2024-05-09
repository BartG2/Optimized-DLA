#include "Quadtree.h"

Quadtree::Quadtree(Rectangle bounds) : bounds(bounds) {}

bool Quadtree::insert(Particle* p) {
    if (!CheckCollisionPointRec(p->position, bounds)) {                     
        return false; // Particle outside bounds
    }

    if (particles.size() < capacity) {
        particles.push_back(p);
        return true;
    }

    // Subdivide if necessary
    if (!divided) {
        subdivide();
    }

    // Try inserting into sub-quadrants
    if (northwest->insert(p)) return true;
    if (northeast->insert(p)) return true;
    if (southwest->insert(p)) return true;
    if (southeast->insert(p)) return true;

    return false; // Should not happen if the logic is correct
}

void Quadtree::subdivide() {
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

void Quadtree::query(Rectangle range, std::vector<Particle*>& result) {
    if (!CheckCollisionRecs(range, bounds)) {                                                                                                      
        return; // No overlap
    }

    for (auto p : particles) {
        if (CheckCollisionPointRec(p->position, range)) {                                                                         
            result.push_back(p);
        }
    }

    if (divided) {
        northwest->query(range, result);
        northeast->query(range, result);
        southwest->query(range, result);
        southeast->query(range, result);
    }
}

void Quadtree::clear() {
    particles.clear();
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
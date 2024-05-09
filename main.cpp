#include <iostream>
#include "raylib.h"
#include <vector>
#include <random>

using namespace std;

enum MyColor {
    red, green
};

class Particle {
public: // Make members public for easy access    
    Vector2 position;
    Vector2 velocity;
    MyColor color;

    Particle(float x, float y, MyColor color = red) : position({x, y}), color(color) {} // Default to red

    void randomWalk() {
        float speed = 2.0f; // Adjust as needed
        velocity.x = (GetRandomValue(-100, 100) / 100.0f) * speed;
        velocity.y = (GetRandomValue(-100, 100) / 100.0f) * speed;
    }

    void update() {
        position.x += velocity.x;
        position.y += velocity.y;
    }
};

struct Quadtree {
    Rectangle bounds; 
    int capacity = 4;  // Max particles per node
    vector<Particle*> particles;  
    bool divided = false;
    Quadtree* northwest;
    Quadtree* northeast;
    Quadtree* southwest;
    Quadtree* southeast;

    Quadtree(Rectangle bounds) : bounds(bounds) {}

    // Insert particle into the quadtree
    bool insert(Particle* p) {
        if (!CheckCollisionPointRec(p->position, bounds)) {                                                                                                                      //ERROR: class "Rectangle" has no member "CheckCollisionPointRec"
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

    void subdivide() {
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

    // Query for particles in a region
    void query(Rectangle range, vector<Particle*>& result) {
        if (!CheckCollisionRecs(range, bounds)) {                                                                                                                                 //ERROR: class "Rectangle" has no member "CheckCollisionRec", also there is no such function
            return; // No overlap
        }

        for (auto p : particles) {
            if (CheckCollisionPointRec(p->position, range)) {                                                                                                                                //ERROR: class "Rectangle" has no member "CheckCollisionPointRec"
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

    // Clear the quadtree
    void clear() {
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
};

int main() {
    unsigned int screenWidth = 1920; 
    unsigned int screenHeight = 1080; 

    InitWindow(screenWidth, screenHeight, "DLA");
    SetTargetFPS(100);

    // Camera setup
    Camera2D camera = { 0 };
    camera.target = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Initialize particles
    vector<Particle> particles;
    particles.emplace_back(screenWidth / 2.0f, screenHeight / 2.0f, green); // Center particle; green 
    int radius = 120; // Radius of the starting circle
    for (int i = 0; i < 20000; ++i) { // Create initial red particles
        double angle = (double)i / 50.0 * 2.0 * PI;
        particles.emplace_back(screenWidth / 2.0f + radius * cos(angle), screenHeight / 2.0f + radius * sin(angle));
    }

    // Quadtree initialization
    Quadtree quadtree({0, 0, screenWidth, screenHeight}); 

    // Add inital particles to the quadtree
    for (auto& particle : particles) {
        quadtree.insert(&particle);
    }


    while (!WindowShouldClose()) { 
        // Movement
        for (auto &particle : particles) {
            if (particle.color == red) { 
                particle.randomWalk();
                particle.update();
            }
        }

        // Collision and Aggregation using the Quadtree
        for (auto &particle : particles) {
            if (particle.color == red) {
                vector<Particle*> nearbyParticles;
                Rectangle range = {particle.position.x - 2, particle.position.y - 2, 4, 4}; // Small range around the particle
                quadtree.query(range, nearbyParticles);

                for (auto &other : nearbyParticles) {
                    if (other->color == green && CheckCollisionCircles(particle.position, 2, other->position, 2)) {                              //ERROR: other.color must be other->color, same with other.position
                        particle.color = green;
                        particle.velocity = { 0, 0 }; 
                        break; 
                    }
                }
            }
        }

        //Update Quadtree                                                                                                                                           //This was missing!
        quadtree.clear();
        for (auto& particle : particles) {
            quadtree.insert(&particle);
        }

        // Rendering        
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        for (auto &particle : particles) {
            Color trueColor = RED;
            if(particle.color == green) {
                trueColor = GREEN;
            }
            DrawPixelV(particle.position, trueColor); // Size 2 pixels
        }

        EndMode2D();
        DrawFPS(20, 20);
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
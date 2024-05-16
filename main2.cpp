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

class Quadtree {
    Rectangle bounds;
    int capacity; 
    vector<Particle*> particles;
    bool subdivided; 
    Quadtree* northwest;
    Quadtree* northeast;
    Quadtree* southwest;
    Quadtree* southeast;

public:
    Quadtree(Rectangle bounds, int capacity) : 
        bounds(bounds), capacity(capacity), subdivided(false) {}

    bool insert(Particle* particle) {
        if (!bounds.CheckCollisionPointRec(particle->position)) {
            return false; // Outside bounds
        }

        if (particles.size() < capacity || !subdivided) {
            particles.push_back(particle);
            return true;
        }

        // Subdivide if necessary
        if (!subdivided) {
            subdivide(); 
        }

        // Insert into one of the child quadtrees
        if (northwest->insert(particle)) return true;
        if (northeast->insert(particle)) return true;
        if (southwest->insert(particle)) return true;
        if (southeast->insert(particle)) return true;

        return false; // Should never reach here 
    }


    vector<Particle*> query(Rectangle range) {
        vector<Particle*> result;

        if (!bounds.CheckCollisionRec(range)) {
            return result; // Empty
        }

        result.insert(result.begin(), particles.begin(), particles.end()); 

        if (subdivided) {
            vector<Particle*> nwRes = northwest->query(range);
            vector<Particle*> neRes = northeast->query(range);
            vector<Particle*> swRes = southwest->query(range);
            vector<Particle*> seRes = southeast->query(range);

            result.insert(result.end(), nwRes.begin(), nwRes.end());
            result.insert(result.end(), neRes.begin(), neRes.end());
            result.insert(result.end(), swRes.begin(), swRes.end());
            result.insert(result.end(), seRes.begin(), seRes.end());
        }

        return result;
    }

    void subdivide() {
        // Code to create quadrants for northwest, northeast, southwest, southeast                                                  //ERROR code without implementation :(
        subdivided = true;
    }
};

int main() {
    unsigned int screenWidth = 800; 
    unsigned int screenHeight = 600; 

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
    int radius = 100; // Radius of the starting circle
    for (int i = 0; i < 500; ++i) { // Create initial red particles
        double angle = (double)i / 50.0 * 2.0 * PI;
        particles.emplace_back(screenWidth / 2.0f + radius * cos(angle), screenHeight / 2.0f + radius * sin(angle));
    }

    Quadtree quadtree({0, 0, screenWidth, screenHeight}, 4); // Adjust capacity

    while (!WindowShouldClose()) { 
        // Movement
        for (auto &particle : particles) {
            if (particle.color == red) { 
                particle.randomWalk();
                particle.update();
            }
        }

        // Collision and Aggregation
        for (auto& particle : particles) {
            if (particle.color == red) {
                vector<Particle*> nearby = quadtree.query(Rectangle{particle.position.x - 2, particle.position.y - 2, 4, 4});

                for (auto& other : nearby) { 
                    if (other.color == green && CheckCollisionPointCircle(particle.position, other.position, 2)) {
                        particle.color = green;
                        particle.velocity = {0, 0};
                        break; // Stop checking
                    }
                }
            }
        }

        // Update quadtree
        quadtree.clear(); // Clear the quadtree (not fully shown for brevity)
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
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
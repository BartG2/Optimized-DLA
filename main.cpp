#include <iostream>
#include "raylib.h"
#include <vector>
#include <random>

#include "Particle.h"
#include "Quadtree.h"

using namespace std;

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
    for (int i = 0; i < 10000; ++i) { // Create initial red particles
        double angle = (double)i / 50.0 * 2.0 * PI;
        particles.emplace_back(screenWidth / 2.0f + radius * cos(angle), screenHeight / 2.0f + radius * sin(angle));
        particles.emplace_back(screenWidth / 2.0f + 2 * radius * cos(angle), screenHeight / 2.0f + 2 * radius * sin(angle));
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
                    if (other->color == green && CheckCollisionCircles(particle.position, 2, other->position, 2)) {                            
                        particle.color = green;
                        particle.velocity = { 0, 0 }; 
                        break; 
                    }
                }
            }
        }

        //Update Quadtree                                                                                                                   
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
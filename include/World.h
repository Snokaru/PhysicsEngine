#ifndef WORLD_H
#define WORLD_H
#include "PhysicsBody.h"
#include "CollisionData.h"
#include <vector>

class World
{
    public:
        // Collision Detection Routines
        World(int steps = 10, int iterations = 10);
        void update();
        void step();
        void add_body(PhysicsBody* body);
        std::vector<PhysicsBody*> get_bodies() {
            return physics_bodies;
        }
        void set_dt(double dt) {
            this->dt = dt;}

    private:
        double dt;
        int steps;
        int iterations;
        double interp;
        std::vector<PhysicsBody*> physics_bodies;
        std::vector<CollisionData*> contacts;
};

#endif // WORLD_H

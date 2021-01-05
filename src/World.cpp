#include "World.h"
#include "CollisionChecker.h"
#include "CollisionSolver.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>

World::World(int steps, int iterations) {
    this->steps = steps;
    this->iterations = iterations;
}

void World::update() {
    this->step();

    for (auto i = physics_bodies.begin(); i != physics_bodies.end(); ++i) {
        (*i)->set_force(Vector2f(0, 0));
    }
}

void World::step() {
    contacts.clear();
    Vector2f gravity(0.0d, 100.0d);

    for (auto i = physics_bodies.begin(); i != physics_bodies.end(); ++i) {
        for (auto j = i + 1; j != physics_bodies.end(); ++j) {
            if (CollisionChecker::check_collision(*i, *j) == true) {
                CollisionData* contact_info = CollisionSolver::check_collision(*i, *j);
                if (contact_info != nullptr) {
                    contacts.push_back(contact_info);
                }
            }
        }
    }


    for (auto i = physics_bodies.begin(); i != physics_bodies.end(); ++i) {
        (*i)->integrate_forces(dt, gravity);
    }
    for (auto i = contacts.begin(); i != contacts.end(); ++i) {
        (*i)->solve();
    }

    for (auto i = physics_bodies.begin(); i != physics_bodies.end(); ++i) {
        (*i)->integrate_velocity(dt, gravity);
    }


    /*
    for (auto i = contacts.begin(); i != contacts.end(); ++i) {
        (*i)->positional_correction();
    }*/

    for (auto i = contacts.begin(); i != contacts.end(); i++) {
        delete *i;
    }

}

void World::add_body(PhysicsBody* body) {
    physics_bodies.push_back(body);
}


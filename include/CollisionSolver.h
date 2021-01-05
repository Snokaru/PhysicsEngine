#ifndef COLLISIONSOLVER_H
#define COLLISIONSOLVER_H
#include "PhysicsBody.h"
#include "Circle.h"
#include "AABB.h"
#include "CollisionData.h"

namespace CollisionSolver
{
    CollisionData* check_collision(PhysicsBody* b1, PhysicsBody* b2);
    CollisionData* AABB_vs_circle(PhysicsBody* aabb, PhysicsBody* circle);
    CollisionData* AABB_vs_AABB(PhysicsBody* aabb1, PhysicsBody* aabb2);
    CollisionData* circle_vs_circle(PhysicsBody* circle1, PhysicsBody* circle2);
};

#endif // COLLISIONSOLVER_H

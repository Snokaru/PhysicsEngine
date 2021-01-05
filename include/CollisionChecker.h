#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "PhysicsBody.h"
#include "Circle.h"
#include "AABB.h"
#include "CollisionData.h"

namespace CollisionChecker
{
    bool check_collision(PhysicsBody* b1, PhysicsBody* b2);
    bool AABB_vs_circle(PhysicsBody* aabb, PhysicsBody* circle);
    bool AABB_vs_AABB(PhysicsBody* aabb1, PhysicsBody* aabb2);
    bool circle_vs_circle(PhysicsBody* circle1, PhysicsBody* circle2);
};

#endif // COLLISIONCHECKER_H

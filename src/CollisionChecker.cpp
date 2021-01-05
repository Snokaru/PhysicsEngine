#include "CollisionChecker.h"
#include "Shape.h"
#include "Circle.h"
#include "CollisionData.h"
#include "MathUtils.h"
#include <cmath>
#include <iostream>

bool CollisionChecker::check_collision(PhysicsBody* b1, PhysicsBody* b2) {
    Circle *circle1 = nullptr, *circle2 = nullptr;
    AABB *aabb1 = nullptr, *aabb2 = nullptr;
    Shape* b1_shape = b1->get_shape();
    Shape* b2_shape = b2->get_shape();

    if (dynamic_cast<Circle*>(b1_shape)) {
        circle1 = dynamic_cast<Circle*>(b1_shape);
    }
    else if (dynamic_cast<AABB*>(b1_shape)) {
        aabb1 = dynamic_cast<AABB*>(b1_shape);
    }

    if (dynamic_cast<Circle*>(b2_shape)) {
        circle2 = dynamic_cast<Circle*>(b2_shape);
    }
    else if (dynamic_cast<AABB*>(b2_shape)) {
        aabb2 = dynamic_cast<AABB*>(b2_shape);
    }
    if (circle1 != nullptr && aabb2 != nullptr)
        return AABB_vs_circle(b2, b1);
    if (circle1 != nullptr && circle2 != nullptr)
        return circle_vs_circle(b1, b2);
    if (aabb1 != nullptr && circle2 != nullptr)
        return AABB_vs_circle(b1, b2);
    if (aabb1 != nullptr && aabb2 != nullptr)
        return AABB_vs_AABB(b1, b2);
}

bool CollisionChecker::AABB_vs_circle(PhysicsBody* aabb, PhysicsBody* circle)
{
    AABB* aabb_shape = dynamic_cast<AABB*>(aabb->get_shape());
    Circle* circle_shape = dynamic_cast<Circle*>(circle->get_shape());

    double nx = circle_shape->get_position().x - aabb_shape->get_position().x - aabb_shape->get_width() / 2;
    double ny = circle_shape->get_position().y - aabb_shape->get_position().y - aabb_shape->get_height() / 2;

    double x_overlap = circle_shape->get_radius() + aabb_shape->get_width() / 2 - std::abs(nx);
    double y_overlap = circle_shape->get_radius() + aabb_shape->get_height() / 2 - std::abs(ny);

    return x_overlap > 0 && y_overlap > 0;
}

bool CollisionChecker::AABB_vs_AABB(PhysicsBody* aabb1, PhysicsBody* aabb2)
{
    AABB* aabb1_shape = dynamic_cast<AABB*>(aabb1->get_shape());
    AABB* aabb2_shape = dynamic_cast<AABB*>(aabb2->get_shape());

    if (aabb1_shape->get_position().x + aabb1_shape->get_width() < aabb2_shape->get_position().x || aabb1_shape->get_position().x > aabb2_shape->get_position().x + aabb2_shape->get_width()) {
        return false;
    } else if (aabb1_shape->get_position().y + aabb1_shape->get_height() < aabb2_shape->get_position().y || aabb1_shape->get_position().y > aabb2_shape->get_position().y + aabb2_shape->get_height()) {
        return false;
    } else
        return true;
}

bool CollisionChecker::circle_vs_circle(PhysicsBody* circle1, PhysicsBody* circle2) {
    Circle* circle1_shape = dynamic_cast<Circle*>(circle1->get_shape());
    Circle* circle2_shape = dynamic_cast<Circle*>(circle2->get_shape());

    double nx = circle2_shape->get_position().x - circle1_shape->get_position().x;
    double ny = circle2_shape->get_position().y - circle1_shape->get_position().y;
    double radius = circle1_shape->get_radius() + circle2_shape->get_radius();

    return nx * nx + ny * ny <= radius * radius;
}



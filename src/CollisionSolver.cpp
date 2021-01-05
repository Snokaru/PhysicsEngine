#include "CollisionSolver.h"
#include "Shape.h"
#include "Circle.h"
#include "CollisionData.h"
#include "MathUtils.h"
#include <cmath>
#include <iostream>

CollisionData* CollisionSolver::check_collision(PhysicsBody* b1, PhysicsBody* b2) {
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

CollisionData* CollisionSolver::AABB_vs_circle(PhysicsBody* aabb, PhysicsBody* circle)
{
    AABB* aabb_shape = dynamic_cast<AABB*>(aabb->get_shape());
    Circle* circle_shape = dynamic_cast<Circle*>(circle->get_shape());

    /*
    Vector2f result;
    double penetration;

    // Vector from A to B
    Vector2f n = (aabb_shape->get_position() + Vector2f(aabb_shape->get_width() / 2, aabb_shape->get_height() / 2)) - (circle_shape->get_position() + Vector2f(circle_shape->get_radius(), circle_shape->get_radius()));

    // Closest point on A to center of B
    Vector2f closest = n;

    // Calculate half extents along each axis
    double x_extent = aabb_shape->get_width() / 2;
    double y_extent = aabb_shape->get_height() / 2;

    // Clamp point to edges of the AABB
    closest.x = clamp(closest.x, -x_extent, x_extent);
    closest.y = clamp(closest.y, -y_extent, y_extent);

    bool inside = false;

    // Circle is inside the AABB, so we need to clamp the circle's center
    // to the closest edge
    if (n == closest) {
        inside = true;

        // Find closest axis
        if (std::abs(n.x) > std::abs(n.y)) {
            // Clamp to closest extent
            if(closest.x > 0)
                closest.x = x_extent;
            else
                closest.x = -x_extent;
        }

        // y axis is shorter
        else {
            // Clamp to closest extent
            if(closest.y > 0)
                closest.y = y_extent;
            else
                closest.y = -y_extent;
        }
    }

    Vector2f normal = n - closest;
    double length = normal.length();
    double d = length * length;
    double r = circle_shape->get_radius();

    // Early out of the radius is shorter than distance to closest point and
    // Circle not inside the AABB
    if (d > r * r && !inside)
        return nullptr;

    // Avoided sqrt until we needed
    d = std::sqrt(d);

    // Collision normal needs to be flipped to point outside if circle was
    // inside the AABB
    if (inside) {
        result = Vector2f(-normal.x / length, -normal.y / length);
        penetration = r - d;
    }
    else {
        result = Vector2f(normal.x / length, normal.y / length);
        penetration = r - d;
    }
    return new CollisionData(aabb, circle, penetration, result);
    */

    double dx = circle_shape->get_position().x - (aabb_shape->get_position().x + aabb_shape->get_width() / 2);
    double dy = circle_shape->get_position().y - (aabb_shape->get_position().y + aabb_shape->get_height() / 2);
    double ox = dx > 0.0 ? aabb_shape->get_width() / 2 : -aabb_shape->get_width() / 2;
    double oy = dy > 0.0 ? aabb_shape->get_height() / 2 : -aabb_shape->get_height() / 2;
    double cx = 0;
    double cy = 0;

    if (std::abs(dx) > aabb_shape->get_width() / 2 && std::abs(dy) > aabb_shape->get_height() / 2) {
        cx = aabb_shape->get_position().x + aabb_shape->get_width() / 2 + ox;
        cy = aabb_shape->get_position().y + aabb_shape->get_height() / 2 + oy;
    } else if ((dy < -aabb_shape->get_height() / 2 || dy > aabb_shape->get_height() / 2) && dx < aabb_shape->get_width() / 2 && dx > -aabb_shape->get_width() / 2) {
        cx = aabb_shape->get_position().x + aabb_shape->get_width() / 2 + dx;
        cy = aabb_shape->get_position().y + aabb_shape->get_height() / 2 + oy;
    } else {
        cx = aabb_shape->get_position().x + aabb_shape->get_width() / 2 + ox;
        cy = aabb_shape->get_position().y + aabb_shape->get_height() / 2 + dy;
    }

    double cdx = cx - circle_shape->get_position().x;
    double cdy = cy - circle_shape->get_position().y;

    if (cdx * cdx + cdy * cdy <= circle_shape->get_radius() * circle_shape->get_radius()) {
        double dist = std::sqrt(cdx * cdx + cdy * cdy);
        Vector2f normal(cdx / dist, cdy / dist);
        std::vector<Vector2f> contacts;
        contacts.push_back(Vector2f(cx, cy));
        double penetration = circle_shape->get_radius();
        return new CollisionData(circle, aabb, penetration, normal, contacts);
    }

    return nullptr;
}
CollisionData* CollisionSolver::AABB_vs_AABB(PhysicsBody* aabb1, PhysicsBody* aabb2)
{

    AABB* aabb1_shape = dynamic_cast<AABB*>(aabb1->get_shape());
    AABB* aabb2_shape = dynamic_cast<AABB*>(aabb2->get_shape());
    /*
    double penetration;
    Vector2f normal;

    // Vector from A to B

    Vector2f n = (aabb1_shape->get_position() + Vector2f(aabb1_shape->get_width() / 2, aabb1_shape->get_height() / 2)) - (aabb2_shape->get_position() + Vector2f(aabb2_shape->get_width() / 2, aabb2_shape->get_height() / 2));

    // Calculate half extents along x axis for each object
    double a_extent_x = aabb1_shape->get_width() / 2;
    double b_extent_x = aabb2_shape->get_width() / 2;

    // Calculate overlap on x axis
    double x_overlap = a_extent_x + b_extent_x - std::abs(n.x);

    // SAT test on x axis
    if (x_overlap > 0)
    {
        // Calculate half extents along x axis for each object
        double a_extent_y = aabb1_shape->get_height() / 2;
        double b_extent_y = aabb2_shape->get_height() / 2;

        // Calculate overlap on y axis
        double y_overlap = a_extent_y + b_extent_y - std::abs(n.y);
        std::cout << "x_overlap: " << x_overlap << ", " << "y_overlap: " << y_overlap << "\n";
        // SAT test on y axis
        if (y_overlap > 0) {
            // Find out which axis is axis of least penetration
            if (x_overlap < y_overlap) {
                // Point towards B knowing that n points from A to B
                if(n.x < 0)
                    normal = Vector2f(1, 0);
                else
                    normal = Vector2f(-1, 0);
                penetration = x_overlap;
                return new CollisionData(aabb1, aabb2, penetration, normal);
            }
            else {
                // Point toward B knowing that n points from A to B
                if (n.y < 0)
                    normal = Vector2f(0, -1);
                else
                    normal = Vector2f(0, 1);
                penetration = y_overlap;
                return new CollisionData(aabb1, aabb2, penetration, normal);
            }
        }
    }
    return nullptr;*/
    double nx = aabb1_shape->get_position().x + aabb1_shape->get_width() / 2 - (aabb2_shape->get_position().x + aabb2_shape->get_width() / 2);
    double ny = aabb1_shape->get_position().y + aabb1_shape->get_height() / 2 - (aabb2_shape->get_position().y + aabb2_shape->get_height() / 2);

    double x_overlap = aabb1_shape->get_width() / 2 + aabb2_shape->get_width() / 2 - std::abs(nx);
    if (x_overlap > 0) {
        double y_overlap = aabb1_shape->get_height() / 2 + aabb2_shape->get_height() / 2 - std::abs(ny);
        if (y_overlap > 0) {
            if (x_overlap < y_overlap) {
                Vector2f normal(nx < 0.0 ? 1.0 : -1.0, 0.0);
                double penetration = x_overlap;

                double x = normal.x > 0.0 ? aabb2_shape->get_position().x : aabb2_shape->get_position().x + aabb2_shape->get_width();
                std::vector<Vector2f> contacts;
                contacts.push_back(Vector2f(x, std::max(aabb2_shape->get_position().y, aabb1_shape->get_position().y)));
                contacts.push_back(Vector2f(x, std::min(aabb2_shape->get_position().y + aabb2_shape->get_height(), aabb1_shape->get_position().y + aabb1_shape->get_height())));
                return new CollisionData(aabb1, aabb2, penetration, normal, contacts);
            } else {
                Vector2f normal(0.0, ny < 0.0 ? 1.0 : -1.0);
                double penetration = y_overlap;

                double y = normal.y > 0.0 ? aabb2_shape->get_position().y : aabb2_shape->get_position().y + aabb2_shape->get_height();
                std::vector<Vector2f> contacts;
                contacts.push_back(Vector2f(std::max(aabb2_shape->get_position().x, aabb1_shape->get_position().x), y));
                contacts.push_back(Vector2f(std::min(aabb2_shape->get_position().x + aabb2_shape->get_width(), aabb1_shape->get_position().x + aabb1_shape->get_width()), y));
                return new CollisionData(aabb1, aabb2, penetration, normal, contacts);
            }
        }
    }
    return nullptr;
}
CollisionData* CollisionSolver::circle_vs_circle(PhysicsBody* circle1, PhysicsBody* circle2) {
    Circle* circle1_shape = dynamic_cast<Circle*>(circle1->get_shape());
    Circle* circle2_shape = dynamic_cast<Circle*>(circle2->get_shape());
    /*
    double penetration;
    Vector2f normal = (circle1_shape->get_position() + Vector2f(circle1_shape->get_radius(), circle1_shape->get_radius())) - (circle2_shape->get_position() + Vector2f(circle2_shape->get_radius(), circle2_shape->get_radius()));

    double r = circle1_shape->get_radius() + circle2_shape->get_radius();

    double n_length = normal.length();
    if (n_length * n_length > r * r)
        return nullptr;

    if (n_length >= 0) {
        penetration = r - n_length;
        normal = Vector2f(normal.x / n_length, normal.y / n_length);
        return new CollisionData(circle1, circle2, penetration, normal);
    }
    else {
        // Choose random (but consistent) values
        penetration = circle1_shape->get_radius();
        normal = Vector2f(1, 0);
        return new CollisionData(circle1, circle2, penetration, normal);
    }
    */
    double nx = circle2_shape->get_position().x - circle1_shape->get_position().x;
    double ny = circle2_shape->get_position().y - circle1_shape->get_position().y;
    double distance = std::sqrt(nx * nx + ny * ny);
    double radius = circle1_shape->get_radius() + circle2_shape->get_radius();

    if (distance == 0.0) {
        double penetration = circle1_shape->get_radius();
        Vector2f normal(1, 0);
        std::vector<Vector2f> contacts;
        contacts.push_back(circle1_shape->get_position());

        return new CollisionData(circle1, circle2, penetration, normal, contacts);
    } else {
        double penetration = radius - distance;
        Vector2f normal(nx / distance, ny / distance);
        std::vector<Vector2f> contacts;
        contacts.push_back(Vector2f(normal.x * circle1_shape->get_radius() + circle1_shape->get_position().x, normal.y * circle1_shape->get_radius() + circle1_shape->get_position().y));

        return new CollisionData(circle1, circle2, penetration, normal, contacts);

    }

}



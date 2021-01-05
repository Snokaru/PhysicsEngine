#include "CollisionData.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>

CollisionData::CollisionData(PhysicsBody* first_body, PhysicsBody* second_body, double penetration, Vector2f normal, std::vector<Vector2f> contact_points)
{
    this->contact_points = contact_points;
    this->set_first_body(first_body);
    this->set_second_body(second_body);
    this->set_penetration(penetration);
    this->set_normal(normal);
    this->min_restitution = std::min(first_body->get_material().get_restitution(), second_body->get_material().get_restitution());
}

void CollisionData::set_first_body(PhysicsBody* first_body) {
    this->first_body = first_body;
}
void CollisionData::set_second_body(PhysicsBody* second_body) {
    this->second_body = second_body;
}
void CollisionData::set_penetration(double penetration) {
    this->penetration = penetration;
}
void CollisionData::set_normal(Vector2f normal) {
    this->normal = normal;
}

PhysicsBody* CollisionData::get_first_body() {
    return first_body;
}
PhysicsBody* CollisionData::get_second_body() {
    return second_body;
}
double CollisionData::get_penetration() {
    return penetration;
}
Vector2f CollisionData::get_normal() {
    return normal;
}

void CollisionData::solve()
{
    /*
    std::cout << "Solving Collision For penetration=" << penetration << " and normal=(" << normal.x << "," << normal.y << ")\n";
    std::cout << "Testing if bodies are static\n";
    std::cout << *first_body << " " << *second_body << std::endl;
    std::cout << first_body->get_mass_data().get_inverse_mass() << "!!!" << second_body->get_mass_data().get_inverse_mass() << std::endl;
    if (first_body->get_mass_data().get_inverse_mass() == 0 && second_body->get_mass_data().get_inverse_mass() == 0) {

        infinite_mass_correction();
        return;
    }

    std::cout << "Computing relative velocity\n";
    // Calculate relative velocity
    Vector2f rv = first_body->get_velocity() - second_body->get_velocity();
    std::cout << "Relative Velocity: " << rv << std::endl;
    // Calculate relative velocity in terms of the normal direction
    double velocity_along_normal = rv * normal;
    std::cout << "Velocity Along Normal: " << velocity_along_normal << std::endl;

    // Do not resolve if velocities are separating
    if(velocity_along_normal > 0)
        return;

    // Calculate restitution
    double min_restitution = std::min(first_body->get_material().get_restitution(), second_body->get_material().get_restitution());

    // Calculate impulse scalar
    double j = -(1.0d + min_restitution) * velocity_along_normal;
    std::cout << "Scalar Impuse: " << j << std::endl;
    j /= first_body->get_mass_data().get_inverse_mass() + second_body->get_mass_data().get_inverse_mass();
    std::cout << "Scalar Impuse: " << j << std::endl;

    // Apply impulse
    Vector2f impulse = normal * j;
    std::cout << "Impulse * Inverse Mass(x:" << impulse * first_body->get_mass_data().get_inverse_mass();
    first_body->set_velocity(first_body->get_velocity() + impulse * first_body->get_mass_data().get_inverse_mass());
    second_body->set_velocity(second_body->get_velocity() - impulse * second_body->get_mass_data().get_inverse_mass());
    std::cout << "First Body Velocity: " << first_body->get_velocity();*/

    for (auto i = 0; i < contact_points.size(); i++) {
        double rvx = second_body->get_velocity().x - first_body->get_velocity().x;
        double rvy = second_body->get_velocity().y - first_body->get_velocity().y;
        double velocity_along_normal = rvx * this->normal.x + rvy * this->normal.y;

        if (velocity_along_normal <= 0) {
            double rax = contact_points[i].x - first_body->get_shape()->get_position().x;
            double ray = contact_points[i].y - first_body->get_shape()->get_position().y;
            double rbx = contact_points[i].x - second_body->get_shape()->get_position().x;
            double rby = contact_points[i].y - second_body->get_shape()->get_position().y;

            double im_sum = first_body->get_mass_data().get_inverse_mass() + second_body->get_mass_data().get_inverse_mass();
            double j = -(1.0 + this->min_restitution) * velocity_along_normal;
            j /= im_sum;
            j /= this->contact_points.size();

            first_body->apply_raw_impulse(-j * this->normal.x, -j * this->normal.y, rax, ray);
            second_body->apply_raw_impulse(j * this->normal.x, j * this->normal.y, rbx, rby);
        }
    }
}

void CollisionData::positional_correction() {
    double percent = 0.2;
    double slop = 0.01;
    double m = std::max(this->penetration - slop, 0.0) / (first_body->get_mass_data().get_inverse_mass() + second_body->get_mass_data().get_inverse_mass());

    double cx = m * this->normal.x * percent;
    double cy = m * this->normal.y * percent;

    first_body->get_shape()->set_position(first_body->get_shape()->get_position() - Vector2f(cx * first_body->get_mass_data().get_inverse_mass(), cy * first_body->get_mass_data().get_inverse_mass()));
    second_body->get_shape()->set_position(second_body->get_shape()->get_position() + Vector2f(cx * second_body->get_mass_data().get_inverse_mass(), cy * second_body->get_mass_data().get_inverse_mass()));

}

void CollisionData::infinite_mass_correction() {
    this->first_body->set_velocity(Vector2f(0, 0));
    this->second_body->set_velocity(Vector2f(0, 0));
}





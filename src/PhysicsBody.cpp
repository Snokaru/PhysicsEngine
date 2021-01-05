#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(Shape* shape, Material material, MassData mass_data, Vector2f velocity, Vector2f force, double gravity_scale)
{
    this->set_shape(shape);
    this->set_material(material);
    this->set_mass_data(mass_data);
    this->set_velocity(velocity);
    this->set_force(force);
    this->set_gravity_scale(gravity_scale);
}

// TODO: Fix Encapsulation Error
Shape* PhysicsBody::get_shape() {
    return shape;
}

Material PhysicsBody::get_material() {
    return material;
}

MassData PhysicsBody::get_mass_data() {
    return mass_data;
}

Vector2f PhysicsBody::get_velocity() {
    return velocity;
}

Vector2f PhysicsBody::get_force() {
    return force;
}

double PhysicsBody::get_gravity_scale() {
    return gravity_scale;
}

void PhysicsBody::set_shape(Shape* shape) {
    this->shape = shape;
}

void PhysicsBody::set_material(Material material) {
    this->material = material;
}

void PhysicsBody::set_mass_data(MassData mass_data) {
    this->mass_data = mass_data;
}

void PhysicsBody::set_velocity(Vector2f velocity) {
    this->velocity = velocity;
}

void PhysicsBody::set_force(Vector2f force) {
    this->force = force;
}

void PhysicsBody::set_gravity_scale(double gravity_scale) {
    this->gravity_scale = gravity_scale;
}

PhysicsBody::~PhysicsBody() {
    delete shape;
}

void PhysicsBody::integrate_forces(double dt, Vector2f gravity) {
    if (this->get_mass_data().get_inverse_mass() == 0)
        return;
    this->velocity.x += (this->force.x * this->mass_data.get_inverse_mass() + gravity.x) * (dt / 2.0);
    this->velocity.y += (this->force.y * this->mass_data.get_inverse_mass() + gravity.y) * (dt / 2.0);
    this->angular_velocity += this->torque * this->inverse_inertia * (dt / 2.0);
}

void PhysicsBody::integrate_velocity(double dt, Vector2f gravity) {
    if(this->get_mass_data().get_inverse_mass() == 0)
        return;
    this->get_shape()->set_position(this->get_shape()->get_position() + this->velocity * dt);
    this->orientation += this->angular_velocity * dt;
    this->integrate_forces(dt, gravity);
}

void PhysicsBody::apply_impulse(Vector2f velocity, Vector2f angular_velocity) {
    this->apply_raw_impulse(velocity.x, velocity.y, angular_velocity.x, angular_velocity.y);
}


void PhysicsBody::apply_raw_impulse(double x, double y, double rx, double ry) {
    this->velocity.x += this->get_mass_data().get_inverse_mass() * x;
    this->velocity.y += this->get_mass_data().get_inverse_mass() * y;
    this->angular_velocity += this->inverse_inertia * (rx * y - ry * x);
}




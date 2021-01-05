#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H
#include "MathUtils.h"
#include "Shape.h"
#include "MassData.h"
#include "Material.h"
#include <iostream>

class PhysicsBody
{
    public:
        PhysicsBody(Shape*, Material, MassData, Vector2f, Vector2f, double);
        ~PhysicsBody();

        Shape*      get_shape();
        Material    get_material();
        MassData    get_mass_data();
        Vector2f    get_velocity();
        Vector2f    get_force();
        double      get_gravity_scale();

        void        set_shape(Shape*);
        void        set_material(Material);
        void        set_mass_data(MassData);
        void        set_velocity(Vector2f);
        void        set_force(Vector2f);
        void        set_gravity_scale(double);

        void        integrate_forces(double dt, Vector2f gravity);
        void        integrate_velocity(double dt, Vector2f gravity);
        void        apply_impulse(Vector2f velocity, Vector2f angular_velocity);
        void        apply_raw_impulse(double x, double y, double rx, double ry);

        friend std::ostream& operator<<(std::ostream& out, const PhysicsBody& body) {
            out << "PhysicsBody(" << body.velocity.x << "," << body.velocity.y << ")";
            return out;
        }

    private:
        Shape*      shape;
        Material    material;
        MassData    mass_data;
        Vector2f    velocity;
        Vector2f    force;
        double      gravity_scale;
        double      inertia;
        double      inverse_inertia;
        double      angular_velocity;
        double      torque;
        double      orientation;
        double      static_friction;
        double      kinetic_friction;

};

#endif // PHYSICSBODY_H

#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H
#include "MathUtils.h"
#include "PhysicsBody.h"
#include <vector>

class CollisionData
{
    public:
        CollisionData(PhysicsBody*, PhysicsBody*, double, Vector2f, std::vector<Vector2f>);

        void set_first_body(PhysicsBody* first_shape);
        void set_second_body(PhysicsBody* second_shape);
        void set_penetration(double penetration);
        void set_normal(Vector2f normal);
        void solve();

        PhysicsBody* get_first_body();
        PhysicsBody* get_second_body();
        double get_penetration();
        Vector2f get_normal();
        void positional_correction();
        void infinite_mass_correction();

    private:
        PhysicsBody* first_body;
        PhysicsBody* second_body;
        double penetration;
        double min_restitution;
        double static_friction;
        double kinetic_friction;
        Vector2f normal;
        std::vector<Vector2f> contact_points;

        void setup();
};

#endif // COLLISIONDATA_H

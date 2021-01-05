#ifndef CIRCLE_H
#define CIRCLE_H
#include "MathUtils.h"
#include "Shape.h"

class Circle : public Shape {
    public:
        Circle(Vector2f, double);
        void        set_radius(double);
        double      get_radius();

    protected:
        double radius;
};

#endif // CIRCLE_H

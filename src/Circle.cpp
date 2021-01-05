#include "Circle.h"

Circle::Circle(Vector2f position, double radius)
:Shape(position)
{
    this->set_radius(radius);
}

void Circle::set_radius(double radius) {
    this->radius = radius;
}

double Circle::get_radius() {
    return radius;
}


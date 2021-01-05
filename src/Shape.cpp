#include "Shape.h"
#include <iostream>

Shape::Shape(Vector2f position)
{
    this->set_position(position);
}

Vector2f Shape::get_position() {
    return position;
}

void Shape::set_position(Vector2f position) {
    this->position = position;
}

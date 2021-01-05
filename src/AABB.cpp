#include "AABB.h"
#include <iostream>

AABB::AABB(Vector2f position, int width, int height)
:Shape(position)
{
    this->set_width(width);
    this->set_height(height);
}

void AABB::set_width(int width) {
    this->width = width;
}

void AABB::set_height(int height) {
    this->height = height;
}

int AABB::get_width() {
    return width;
}

int AABB::get_height() {
    return height;
}


#ifndef RENDERER_H
#define RENDERER_H
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "AABB.h"
#include "Shape.h"

class Renderer
{
    sf::RenderWindow& window;
    public:
        Renderer(sf::RenderWindow&);
        void render_shape(Shape* shape);
        void render_circle(Circle* circle);
        void render_aabb(AABB* aabb);
};

#endif // RENDERER_H

#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderWindow& window)
:window(window)
{
}

void Renderer::render_shape(Shape* shape) {
    if (dynamic_cast<Circle*>(shape)) {
        render_circle(dynamic_cast<Circle*>(shape));
    } else if (dynamic_cast<AABB*>(shape)) {
        render_aabb(dynamic_cast<AABB*>(shape));
    }
}

void Renderer::render_circle(Circle* circle) {
    sf::CircleShape render_circle(circle->get_radius());
    render_circle.setPosition(circle->get_position().x - circle->get_radius(), circle->get_position().y - circle->get_radius());
    render_circle.setOutlineColor(sf::Color(195, 169, 106));
    render_circle.setFillColor(sf::Color(65, 72, 76));
    render_circle.setOutlineThickness(-2.0d);
    window.draw(render_circle);
}

void Renderer::render_aabb(AABB* aabb) {
    sf::RectangleShape render_rectangle(sf::Vector2f(aabb->get_width(), aabb->get_height()));
    render_rectangle.setPosition(aabb->get_position().x, aabb->get_position().y);
    render_rectangle.setOutlineColor(sf::Color(132, 141, 148));
    render_rectangle.setFillColor(sf::Color(65, 72, 76));
    render_rectangle.setOutlineThickness(-2.0d);
    window.draw(render_rectangle);
}

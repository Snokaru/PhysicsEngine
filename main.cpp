#include <iostream>
#include "World.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Physics Engine");
    sf::Clock clock;
    World world;
    std::cout << "Started App" << std::endl;
    AABB* aabb = new AABB(Vector2f(500.0d, 200.0d), 50.0d, 50.0d);
    AABB* circle = new AABB(Vector2f(250, 300.0d), 50.0d, 50.0d);
    AABB* aabb2 = new AABB(Vector2f (600.0d, 100.0d), 100.0d, 50.0d);
    Circle* circle1 = new Circle(Vector2f(500.0d, 100.0d), 25.0d);
    Circle* circle2 = new Circle(Vector2f(400.0d, 400.0d), 25.0d);
    Circle* circle3 = new Circle(Vector2f(400.0d, 100.0d), 25.0d);
    Circle* circle4 = new Circle(Vector2f(101.0d, 100.0d), 50.0d);
    AABB* aabb1 = new AABB(Vector2f(100.0d, 500.0d), 400.0d, 100.0d);
    AABB* right_margin = new AABB(Vector2f(1000, 0), 24, 668);
    AABB* left_margin = new AABB(Vector2f(0, 0), 24, 668);
    AABB* floor = new AABB(Vector2f(0, 668), 1024, 100);
    world.add_body(new PhysicsBody(aabb, Material(0.3d, 0.95d), MassData(10.0d), Vector2f(-30.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(circle, Material(0.3d, 0.95d), MassData(10.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(circle1, Material(0.3d, 0.95d), MassData(10.0d), Vector2f(-10.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(floor, Material(0.0d, 1.0d), MassData(0.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(right_margin, Material(0.0d, 1.0d), MassData(0.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(left_margin, Material(0.0d, 1.0d), MassData(0.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(circle2, Material(0.3d, 0.8d), MassData(10.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(circle3, Material(0.3d, 0.8d), MassData(10.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(aabb1, Material(0.0d, 1.0d), MassData(0.0d), Vector2f(0.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(circle4, Material(0.3d, 0.8d), MassData(10.0d), Vector2f(100.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));
    world.add_body(new PhysicsBody(aabb2, Material(0.3d, 0.8d), MassData(10.0d), Vector2f(-50.0d, 0.0d), Vector2f(0.0d, 0.0d), 0.0d));

    Renderer renderer(window);
    bool paused = false;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    paused = !paused;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int random_speed = rand() % 61 + (-30);
                    int random_radius = rand() % 50 + 10;
                    int random_position_x = rand() % 970 + 25;
                    Circle* circle = new Circle(Vector2f(random_position_x, 100), random_radius);
                    world.add_body(new PhysicsBody(circle, Material(0.3, 0.8), MassData(10.0d), Vector2f(random_speed, 0), Vector2f(0, 0), 0.0d));
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "Here!\n";
                    int random_speed = rand() % 61 + (-30);
                    int random_position_x = rand() % 970 + 25;
                    int random_width = rand() % 100 + 20;
                    int random_height = rand() % 100 + 20;
                    AABB* aabb = new AABB(Vector2f(random_position_x, 100), random_width, random_height);
                    world.add_body(new PhysicsBody(aabb, Material(0.3, 0.8), MassData(10.0d), Vector2f(random_speed, 0), Vector2f(0, 0), 0.0d));
                }
            }

        }

        // Reset Timer And Get dt
        float dt = clock.restart().asSeconds();
        world.set_dt(dt);
        if (!paused)
            world.update();
        window.clear(sf::Color(65, 72, 76));
        std::vector<PhysicsBody*> bodies = world.get_bodies();
        for (auto i = bodies.begin(); i != bodies.end(); i++) {
            //std::cout << "(x:" << aabb->get_position().x << ",y:" <<  aabb->get_position().y << ")(w:" << aabb->get_width() << ",h:" << aabb->get_height() << ")\n";
            renderer.render_shape((*i)->get_shape());
        }
        window.display();
    }

    return 0;
}

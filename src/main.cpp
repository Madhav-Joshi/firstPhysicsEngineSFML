#include <SFML/Graphics.hpp>
#include "configuration/configuration.hpp"
#include "events/events.hpp"
#include "solver/solver.hpp"
#include "renderer/renderer.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "SFML window", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(conf::max_framerate);
    window.setMouseCursorVisible(true);

    // Renderer
    Renderer renderer{window};

    // Solver configurations
    Solver ball;
    ball.setConstraint(conf::window_size_f * 0.5f, 450.0f);
    sf::Vector2f spawnPosition = sf::Vector2f(200.0f, 0.0f) + conf::window_size_f * 0.5f;
    ball.addObject(spawnPosition, conf::radius);

    sf::CircleShape shape{conf::radius};
    sf::Vector2f origin{conf::radius, conf::radius};
    shape.setOrigin(origin);
    // shape.setFillColor(sf::Color::Green);

    // // Constraint shape
    // sf::CircleShape constraintShape{ball.m_constraint_radius};
    // constraintShape.setOrigin(sf::Vector2f(ball.m_constraint_radius, ball.m_constraint_radius));
    // constraintShape.setPosition(ball.m_constraint_center);
    // constraintShape.setFillColor(sf::Color::Black);
    // constraintShape.setOutlineColor(sf::Color::White);
    // constraintShape.setPointCount(128);
    // constraintShape.setOutlineThickness(2.0f);

    while (window.isOpen())
    {
        processEvents(window);
        window.clear();

        // std::cout << "position: " << ball.m_objects[0].position.x << " " << ball.m_objects[0].position.y << std::endl;
        shape.setPosition(ball.m_objects[0].position);
        ball.update(conf::dt);

        renderer.render(ball);

        window.display();
    }
}
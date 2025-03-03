#include <SFML/Graphics.hpp>
#include "configuration/configuration.hpp"
#include "events/events.hpp"
#include "solver/solver.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "SFML window", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(conf::max_framerate);
    window.setMouseCursorVisible(true);

    Solver ball;
    sf::Vector2f acc{0.0f, 0.0f};
    ball.addObject(conf::window_size_f*0.5f, acc);
    
    sf::CircleShape shape{conf::radius};
    sf::Vector2f origin{conf::radius, conf::radius};
    shape.setOrigin(origin);
    // shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        processEvents(window);
        window.clear();

        std::cout << "position: " << ball.m_objects[0].position.x << " " << ball.m_objects[0].position.y << std::endl;
        shape.setPosition(ball.m_objects[0].position);
        window.draw(shape);
        ball.update(conf::dt);

        window.display();
    }
}
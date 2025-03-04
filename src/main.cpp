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

    // Set simulation attributes
    const float object_spawn_delay = 0.05f;
    const uint32_t max_objects_count = 200;
    const sf::Vector2f object_spawn_position = sf::Vector2f(200.0f, 0.0f) + conf::window_size_f * 0.5f;
    const float object_spawn_speed = 300.0f;

    // Solver configurations
    Solver balls;
    balls.m_frame_dt = conf::dt;
    balls.setConstraint(conf::window_size_f * 0.5f, 450.0f);

    sf::Clock clock;
    while (window.isOpen())
    {
        processEvents(window);

        // std::cout << "position: " << balls.m_objects[0].position.x << " " << balls.m_objects[0].position.y << std::endl;
        if (balls.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay)
        {
            clock.restart();
            auto &ball = balls.addObject(object_spawn_position, conf::radius);
            balls.setObjectVelocity(ball, object_spawn_speed * sf::Vector2f{0, 1});
            ball.color = sf::Color::White;
        }

        balls.update();
        window.clear();
        renderer.render(balls);
        window.display();
    }
}
#include <SFML/Graphics.hpp>
#include "configuration/configuration.hpp"
#include "events/events.hpp"
#include "solver/solver.hpp"
#include "renderer/renderer.hpp"
#include "utils/math.hpp"
#include "utils/number_generator.hpp"
#include <iostream>

static sf::Color getRainbow(float t)
{
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * Math::PI);
    const float b = sin(t + 0.66f * 2.0f * Math::PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({conf::window_size.x, conf::window_size.y}), "SFML window", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(conf::max_framerate);
    window.setMouseCursorVisible(true);

    // Renderer
    Renderer renderer{window};

    // Set simulation attributes
    const float object_spawn_delay = 0.001f;
    const uint32_t max_objects_count = 400;
    const sf::Vector2f object_spawn_position = sf::Vector2f(0.0f, -400.0f) + conf::window_size_f * 0.5f;
    const float object_spawn_speed = 900.0f;
    const float object_min_radius = 10.0f;
    const float object_max_radius = 30.0f;
    const float max_angle = 1.5f;

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
            auto &ball = balls.addObject(object_spawn_position, RNGf::getRange(object_min_radius, object_max_radius));

            const float t = balls.getTime();
            const float angle = max_angle * sin(t) + Math::PI * 0.5f;
            balls.setObjectVelocity(ball, object_spawn_speed * sf::Vector2f{static_cast<float>(cos(angle)), static_cast<float>(sin(angle))});
            ball.color = getRainbow(t);
        }

        balls.update();
        window.clear();
        renderer.render(balls);
        window.display();
    }
}
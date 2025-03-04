#pragma once
#include "solver/solver.hpp"

class Renderer
{
public:
    explicit Renderer(sf::RenderTarget &target) : m_target{target} {}

    void render(const Solver &solver) const
    {
        // Render constraint
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraint_background{constraint.z};
        constraint_background.setOrigin(sf::Vector2f(constraint.z, constraint.z));
        constraint_background.setFillColor(sf::Color::Black);
        constraint_background.setOutlineColor(sf::Color::White);
        constraint_background.setOutlineThickness(2.0f);
        constraint_background.setPosition(sf::Vector2f(constraint.x, constraint.y));
        constraint_background.setPointCount(128);
        m_target.draw(constraint_background);

        // Render objects
        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(sf::Vector2f(1.0f, 1.0f));
        const auto &objects = solver.getObjects();
        for (const auto &obj : objects)
        {
            circle.setPosition(obj.position);
            circle.setScale(sf::Vector2f(obj.radius, obj.radius));
            circle.setFillColor(obj.color);
            m_target.draw(circle);
        }
    }

private:
    sf::RenderTarget &m_target;
};
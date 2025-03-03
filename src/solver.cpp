#include "solver/solver.hpp"
#include <iostream>

VerletObject::VerletObject(sf::Vector2f const& position_, sf::Vector2f const& acceleration_)
    : position{position_}, position_last{position_}, acceleration{acceleration_} {};

void VerletObject::update(float dt)
{
    sf::Vector2f newPosition= 2.0f * position - position_last + acceleration * (dt * dt);
    // Update position
    position_last = position;
    position = newPosition;
    // Reset acceleration
    acceleration  = {};
}

void VerletObject::accelerate(sf::Vector2f a)
{
    this->acceleration += a;
}

void VerletObject::setVelocity(sf::Vector2f v, float dt)
{
    position_last = position - (v * dt);
}

void VerletObject::addVelocity(sf::Vector2f v, float dt)
{
    position_last -= v * dt;
}

[[nodiscard]]
sf::Vector2f VerletObject::getVelocity(float dt) const
{
    return (position - position_last) / dt;
}

VerletObject& Solver::addObject(sf::Vector2f const& position, sf::Vector2f const& acceleration)
{
    m_objects.emplace_back(position, acceleration);
    return m_objects.back();
}

void Solver::update(float dt){
    for (auto &object : m_objects)
    {
        object.accelerate(m_gravity);
        object.update(dt);
    }
}
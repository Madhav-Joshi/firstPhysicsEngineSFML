#include "solver/solver.hpp"

VerletObject::VerletObject(sf::Vector2f const& position_, float radius_)
    : position{position_}, position_last{position_}, radius{radius_} {};

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

VerletObject& Solver::addObject(sf::Vector2f const& position, float radius)
{
    m_objects.emplace_back(position, radius);
    return m_objects.back();
}

void Solver::update(float dt){
    applyGravity();
    applyConstraint();
    updateObjects(dt);
}

void Solver::setConstraint(sf::Vector2f position, float radius)
{
    m_constraint_center = position;
    m_constraint_radius = radius;
}

void Solver::applyGravity()
{
    for (auto& obj : m_objects) {
        obj.accelerate(m_gravity);
    }
}

void Solver::applyConstraint()
{
    for (auto& obj : m_objects) {
        const sf::Vector2f v    = m_constraint_center - obj.position;
        const float        dist = sqrt(v.x * v.x + v.y * v.y);
        if (dist > (m_constraint_radius - obj.radius)) {
            const sf::Vector2f n = v / dist;
            obj.position = m_constraint_center - n * (m_constraint_radius - obj.radius);
        }
    }
}

void Solver::updateObjects(float dt)
{
    for (auto& obj : m_objects) {
        obj.update(dt);
    }
}
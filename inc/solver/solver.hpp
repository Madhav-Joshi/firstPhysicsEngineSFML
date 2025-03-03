#pragma once
#include <SFML/Graphics.hpp>
#include "game/physics/object.hpp"

class VerletObject
{
public:
    VerletObject(sf::Vector2f const& position_, sf::Vector2f const& acceleration_);
    ~VerletObject() = default;

    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration;

    void update(float dt);
    void accelerate(sf::Vector2f a);
    void setVelocity(sf::Vector2f v, float dt);
    void addVelocity(sf::Vector2f v, float dt);
    [[nodiscard]] sf::Vector2f getVelocity(float dt) const;
};

class Solver
{
public:
    Solver() = default;
    ~Solver() = default;

    std::vector<VerletObject> m_objects;
    sf::Vector2f m_gravity{0.0f,10.0f};

    VerletObject& addObject(sf::Vector2f const& position, sf::Vector2f const& acceleration);
    void update(float dt);
};

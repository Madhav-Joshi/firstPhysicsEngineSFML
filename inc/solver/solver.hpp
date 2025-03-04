#pragma once
#include <SFML/Graphics.hpp>
#include "game/physics/object.hpp"
#include <cmath>
#include <vector>

class VerletObject
{
public:
    VerletObject(sf::Vector2f const &position_, float radius_);
    ~VerletObject() = default;

    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration{0.0f, 0.0f};
    float radius;
    sf::Color color = sf::Color::White;

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
    sf::Vector2f m_gravity{0.0f, 10000.0f};
    sf::Vector2f m_constraint_center;
    float m_constraint_radius;
    float m_time = 0.0f;
    float m_frame_dt = 0.0f;
    uint32_t m_sub_steps = 8;

    VerletObject &addObject(sf::Vector2f const &position, float radius);
    void update();
    void setConstraint(sf::Vector2f position, float radius);
    void applyGravity();
    void applyConstraint();
    void updateObjects(float dt);
    void setObjectVelocity(VerletObject &object, sf::Vector2f v);
    void checkCollisions(float dt);
    [[nodiscard]] sf::Vector3f getConstraint() const;
    [[nodiscard]] const std::vector<VerletObject> &getObjects() const;
    [[nodiscard]] float getTime() const;
    [[nodiscard]] float getStepDt() const;
    [[nodiscard]] uint64_t getObjectsCount() const;
};

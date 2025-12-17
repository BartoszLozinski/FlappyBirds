#include "Moveable.hpp"

Moveable::Moveable(const Utils::Vector2u& size_, const Utils::Vector2f& position_, const Utils::Vector2f& velocity_)
    : Entity(size_, position_)
    , velocity(velocity_)
{};

Moveable::Moveable(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
    : Moveable(size_, position_, {0.0f, 0.0f})
{};

Utils::Vector2f Moveable::GetVelocity() const
{
    return this->velocity;
}

void Moveable::Move()
{
    this->position += this->velocity;
}
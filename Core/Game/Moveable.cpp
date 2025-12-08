#include "Moveable.hpp"

Moveable::Moveable(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
    : Entity(size_, position_)
{};

Utils::Vector2f Moveable::GetVelocity() const
{
    return this->velocity;
}

void Moveable::SetVelocity(const Utils::Vector2f& velocity_)
{
    this->velocity = velocity_;
}

void Moveable::Move()
{
    this->position += this->velocity;
}
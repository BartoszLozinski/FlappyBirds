#include "Moveable.hpp"

Moveable::Moveable(const Vector2u& size_, const Vector2f& position_)
    : Entity(size_, position_)
{};

Vector2f Moveable::GetVelocity() const
{
    return this->velocity;
}

void Moveable::SetVelocity(const Vector2f& velocity_)
{
    this->velocity = velocity_;
}

void Moveable::Move()
{
    this->position += this->velocity;
}
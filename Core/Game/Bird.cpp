#include "Bird.hpp"

Bird::Bird(const Vector2u& size_, const Vector2f& position_)
    : Moveable(size_, position_)
{};

void Bird::Control()
{
    return;
}
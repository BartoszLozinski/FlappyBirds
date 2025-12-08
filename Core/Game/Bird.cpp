#include "Bird.hpp"

Bird::Bird(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
    : Moveable(size_, position_)
{};

void Bird::Control()
{
    return;
}
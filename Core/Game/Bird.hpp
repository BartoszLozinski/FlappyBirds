#pragma once
#include "Moveable.hpp"

class Bird : public Moveable
{
protected:
public:
    Bird(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
    void Control() override;
};

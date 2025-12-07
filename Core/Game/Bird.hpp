#pragma once
#include "Moveable.hpp"

class Bird : public Moveable
{
protected:
public:
    Bird(const Vector2u& size_, const Vector2f& position_);
    void Control() override;
};

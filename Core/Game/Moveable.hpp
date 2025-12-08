#pragma once

#include "Entity.hpp"

class Moveable : public Entity
{
protected:
    Utils::Vector2f velocity{ 0.0f, 0.0f };
    
public:
    virtual ~Moveable() = default;
    Moveable(const Utils::Vector2u& size_, const Utils::Vector2f& position_);

    Utils::Vector2f GetVelocity() const;
    void SetVelocity(const Utils::Vector2f& velocity_);
    void Move();
};

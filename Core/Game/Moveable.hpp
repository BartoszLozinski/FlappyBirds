#pragma once

#include "Entity.hpp"

class Moveable : public Entity
{
protected:
    Vector2f velocity{ 0.0f, 0.0f };
    
public:
    virtual ~Moveable() = default;
    Moveable(const Vector2u& size_, const Vector2f& position_);

    Vector2f GetVelocity() const;
    void SetVelocity(const Vector2f& velocity_);
    void Move();
};

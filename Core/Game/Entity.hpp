#pragma once

#include "Vector2T.hpp"

class Entity
{
protected:
    Vector2u size{10, 10};
    Vector2f position{100.f, 100.f};

public:
    virtual ~Entity() = default;
    Entity(const Vector2u& size_, const Vector2f& position_);
    
    Vector2f GetPosition() const;
    Vector2u GetSize() const;
    virtual void Control() = 0;
};

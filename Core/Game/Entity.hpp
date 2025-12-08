#pragma once

#include "Utils/Vector2T.hpp"

class Entity
{
protected:
    Utils::Vector2u size{10, 10};
    Utils::Vector2f position{100.f, 100.f};

public:
    virtual ~Entity() = default;
    Entity(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
    
    Utils::Vector2f GetPosition() const;
    Utils::Vector2u GetSize() const;
    virtual void Control() = 0;
};

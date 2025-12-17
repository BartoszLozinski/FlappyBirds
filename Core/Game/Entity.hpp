#pragma once

#include "Utils/Utils.hpp"
#include "Utils/ControlOption.hpp"

class Entity
{
protected:
    Utils::Vector2u size{10, 10};
    Utils::Vector2f position{100.f, 100.f};

    bool isAlive = true;

public:
    virtual ~Entity() = default;
    Entity(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
    
    Utils::Vector2f GetPosition() const;
    Utils::Vector2u GetSize() const;
    inline bool IsAlive() const { return isAlive; }
    inline void Kill() { isAlive = false; };
    virtual void UpdateState() = 0;
};

#pragma once

#include "Moveable.hpp"
#include "Timer.hpp"

class Bird : public Moveable
{
protected:
    Timer jumpTimer{200};
    void ApplyGravity();
    ControlOption currentControlOption = ControlOption::None;

public:
    Bird(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
    void Control(const ControlOption controlOption);
    void UpdateState() override;
    void SetVelocity(const Utils::Vector2f& velocity_);
};

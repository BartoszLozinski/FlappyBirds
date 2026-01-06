#pragma once

#include "Moveable.hpp"
#include "Timer.hpp"

class Bird : public Moveable
{
protected:
    Timer jumpTimer{200};
    ControlOption currentControlOption = ControlOption::None;
    bool isAlive = true;
    unsigned points = 0;
    void ApplyGravity();
    void SetVelocity(const Utils::Vector2f& velocity_);
    [[nodiscard]] bool HitWindowBoundaries() const;

public:
    Bird(const Utils::Vector2u& size_ = Utils::Vector2u{20, 20}, const Utils::Vector2f& position_ = Utils::Vector2f{200, 300});
    void Control(const ControlOption controlOption);
    void UpdateState() override;
    [[nodiscard]] bool IsAlive() const;
    void Kill();
    [[nodiscard]] unsigned GetPoints() const;
    Bird& operator++();
};

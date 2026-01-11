#pragma once

#include "Moveable.hpp"
#include "Utils/ControlOption.hpp"

namespace Game
{
    class Bird : public Moveable
    {
    protected:
        static constexpr unsigned FRAMES_TO_RESET_JUMP_ABILITY = 10;
        
        unsigned framesSinceLastJump = FRAMES_TO_RESET_JUMP_ABILITY;
        ControlOption currentControlOption = ControlOption::None;
        unsigned points = 0;
        void ApplyGravity();
        [[nodiscard]] bool HitWindowBoundaries() const;
        void Jump();
        [[nodiscard]] bool IsAbleToJump() const;

    public:
        Bird(const Utils::Vector2u& size_ = Utils::Vector2u{40, 40}, const Utils::Vector2f& position_ = Utils::Vector2f{200, 300});
        void Control(const ControlOption controlOption);
        void UpdateState() override;
        [[nodiscard]] unsigned GetPoints() const;
        Bird& operator++();
    };
}

#include "Bird.hpp"

Bird::Bird(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
    : Moveable(size_, position_)
{};

void Bird::ApplyGravity()
{
    static constexpr float GRAVITY = 0.3f;
    velocity.y += GRAVITY;
}

void Bird::Control(const ControlOption controlOption)
{
    if (controlOption != ControlOption::None)
        currentControlOption = controlOption;
}

void Bird::SetVelocity(const Utils::Vector2f& velocity_)
{
    this->velocity = velocity_;
}

void Bird::UpdateState()
{
    if (currentControlOption == ControlOption::Jump && jumpTimer.IsExpired())
    {
        jumpTimer.Reset();
        static constexpr float JUMP_SPEED = 6.f;
        static constexpr float MAX_VERTICAL_SPEED = 12.f;
        velocity.y -= JUMP_SPEED;

        if (velocity.y > MAX_VERTICAL_SPEED)
            velocity.y = MAX_VERTICAL_SPEED;
    }

    ApplyGravity();
    Move();
    currentControlOption = ControlOption::None;        
}

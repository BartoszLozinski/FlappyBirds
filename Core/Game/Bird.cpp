#include "Bird.hpp"
#include "Game/GameConfig.hpp"

namespace Game
{
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

    bool Bird::IsAbleToJump() const
    {
        if (framesSinceLastJump < FRAMES_TO_RESET_JUMP_ABILITY)
            return false;
        
        return true;
    }

    void Bird::Jump()
    {
        if (IsAbleToJump())
        {
            framesSinceLastJump = 0;
            static constexpr float JUMP_SPEED = 5.f;
            static constexpr float MAX_VERTICAL_SPEED = 12.f;
            velocity.y -= JUMP_SPEED;

            if (velocity.y > MAX_VERTICAL_SPEED)
                velocity.y = MAX_VERTICAL_SPEED;
        }
    };

    void Bird::UpdateState()
    {
        if (isAlive && HitWindowBoundaries())
            Kill();

        if (isAlive)
        {
            framesSinceLastJump++;
            
            if (currentControlOption == ControlOption::Jump)
                Jump();

            ApplyGravity();
            Move();
        }
        else if (position.y < (Game::Config::WINDOW_HEIGHT - size.y / 2))
        {
            ApplyGravity();
            Move();
        }
        else 
        {
            position.y = (Game::Config::WINDOW_HEIGHT - size.y / 2);
        }

        currentControlOption = ControlOption::None;        
    }

    Bird& Bird::operator++()
    {
        if (isAlive)
            points++;
        
        return *this;
    }

    unsigned Bird::GetPoints() const
    {
        return points;
    }

    bool Bird::HitWindowBoundaries() const
    {
        if ((position.y < size.y * 0.5) || position.y > (Game::Config::WINDOW_HEIGHT - size.y * 0.5))
            return true;
        
        return false;
    }

    unsigned Bird::GetFramesSinceLastJump() const
    {
        return framesSinceLastJump;
    }
}

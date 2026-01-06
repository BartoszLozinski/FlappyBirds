#include "Bird.hpp"
#include "Game/GameConfig.hpp"

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

void Bird::UpdateState()
{
    if (isAlive && HitWindowBoundaries())
        Kill();

    if (isAlive)
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
    }
    else if (position.y < (GameConfig::WINDOW_HEIGHT - size.y))
    {
        ApplyGravity();
        Move();
    }
    else 
    {
        position.y = (GameConfig::WINDOW_HEIGHT - size.y);
    }

    currentControlOption = ControlOption::None;        
}

bool Bird::IsAlive() const
{
    return this->isAlive;
}

void Bird::Kill()
{
    if (isAlive)
        isAlive = false;
}

Bird& Bird::operator++()
{
    points++;
    return *this;
}

unsigned Bird::GetPoints() const
{
    return points;
}

bool Bird::HitWindowBoundaries() const
{
    if ((position.y < size.y * 0.5) || position.y > (GameConfig::WINDOW_HEIGHT - size.y * 0.5))
        return true;
    
    return false;
}
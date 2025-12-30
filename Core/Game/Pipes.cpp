#include "Pipes.hpp"

#include "GameConfig.hpp"

namespace Game
{
    Pipe::Pipe(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
        : Moveable(size_, position_, {-3.0f, 0.0f})
    {};

    void Pipe::UpdateState()
    {
        Move();
    }

    bool Pipe::MovedOutOfTheWindow() const
    {
        if (position.x + size.x < 0)
            return true;
        
        return false;
    }

    void Pipe::ResetPosition(const bool movedOutOfTheWindow)
    {
        if (movedOutOfTheWindow)
        {
            static constexpr float distanceOverlap = 10.f;
            position.x = GameConfig::WINDOW_WIDTH + distanceOverlap;
        }
    }


    /////////////////////////////////////////////////////////////////////////////

    Pipes::Pipes()
        : pipes({Pipe{{horizontalSize, verticalSize}, {GameConfig::WINDOW_WIDTH, outOfWindowOverlap}}, Pipe{{horizontalSize, verticalSize}, {GameConfig::WINDOW_WIDTH, outOfWindowOverlap + verticalSize + verticalDistanceBetweenPipes}}})
    {};

    void Pipes::UpdateState()
    {
        for (auto& pipe : pipes)
        {
            pipe.Move();
        }
    }

    std::span<const Pipe> Pipes::GetPipes() const
    {
        return this->pipes;
    }
}
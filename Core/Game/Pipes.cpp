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

    void Pipe::SetPosition(const Utils::Vector2f& position_)
    {
        this->position = position_;
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
    {
        VerticalShift();
    };

    void Pipes::UpdateState()
    {
        for (auto& pipe : pipes)
        {
            pipe.Move();
        }
    }

    void Pipes::VerticalShift()
    {
        static constexpr float minVerticalShift = -150;
        static constexpr float maxVerticalShift = 150;
    
        const float verticalShift = Utils::RandomGenerator{minVerticalShift, maxVerticalShift}.Generate();

        pipes[0].SetPosition({ pipes[0].GetPosition().x, pipes[0].GetPosition().y + verticalShift });
        pipes[1].SetPosition({ pipes[1].GetPosition().x, pipes[1].GetPosition().y + verticalShift });
    }

    std::span<const Pipe> Pipes::GetPipes() const
    {
        return this->pipes;
    }
}
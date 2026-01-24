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

    void Pipe::ResetPosition(const bool movedOutOfTheWindow, const float xPosition)
    {
        if (movedOutOfTheWindow)
        {
            position.x = xPosition;
        }
    }

    Pipes::Pipes(const unsigned horizontalSize,
                 const unsigned verticalSize, 
                 const float xPosition,
                 const float yPositionTop,
                 const float yPositionBottom)
        : pipesSegment({Pipe{{horizontalSize, verticalSize}, {xPosition, yPositionTop}},
                        Pipe{{horizontalSize, verticalSize}, {xPosition, yPositionBottom}}})
    {};

    Pipes::Pipes()
        : Pipes(80, 500, static_cast<float>(Game::Config::WINDOW_WIDTH), -50, 650)
    {};

    void Pipes::UpdateState()
    {
        for (auto& pipe : pipesSegment)
        {
            pipe.Move();
        }
    }

    void Pipes::VerticalShift(const float yPositionTop, const float yPositionBotton)
    {
        pipesSegment[static_cast<size_t>(PipesSegmentIndex::Top)].SetPosition({ pipesSegment[0].GetPosition().x, yPositionTop });
        pipesSegment[static_cast<size_t>(PipesSegmentIndex::Bottom)].SetPosition({ pipesSegment[1].GetPosition().x, yPositionBotton });
    }

    void Pipes::ResetPosition(const bool movedOutOfTheWindow, const float xPosition, const float yPositionTop, const float yPositionBottom)
    {
        for (auto& pipe : pipesSegment)
        {
            pipe.ResetPosition(movedOutOfTheWindow, xPosition);
            if (movedOutOfTheWindow)
            {
                VerticalShift(yPositionTop, yPositionBottom);
                isScored = false;
            }
        }
    }

    std::span<const Pipe> Pipes::GetPipesSegment() const
    {
        return this->pipesSegment;
    }

    bool Pipes::IsScored() const
    {
        return isScored;
    }

    void Pipes::Score()
    {
        isScored = true;
    }
}

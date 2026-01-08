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

    /////////////////////////////////////////////////////////////////////////////

    Pipes::Pipes(const float xPosition)
        : pipesSegment({Pipe{{horizontalSize, verticalSize}, {xPosition, outOfWindowOverlap}}, Pipe{{horizontalSize, verticalSize}, {xPosition, outOfWindowOverlap + verticalSize + verticalDistanceBetweenPipes}}})
    {
        VerticalShift();
    };

    Pipes::Pipes()
        : Pipes(static_cast<float>(GameConfig::WINDOW_WIDTH))
    {};

    void Pipes::UpdateState()
    {
        for (auto& pipe : pipesSegment)
        {
            pipe.Move();
        }
    }

    void Pipes::VerticalShift()
    {
        static constexpr float minVerticalShift = -150;
        static constexpr float maxVerticalShift = 150;
    
        const float verticalShift = Utils::RandomGenerator{minVerticalShift, maxVerticalShift}.Generate();

        pipesSegment[0].SetPosition({ pipesSegment[0].GetPosition().x, outOfWindowOverlap + verticalShift });
        pipesSegment[1].SetPosition({ pipesSegment[1].GetPosition().x, outOfWindowOverlap + verticalSize + verticalDistanceBetweenPipes + verticalShift });
    }

    void Pipes::ResetPosition(const bool movedOutOfTheWindow, const float xPosition)
    {
        for (auto& pipe : pipesSegment)
        {
            pipe.ResetPosition(movedOutOfTheWindow, xPosition);
            if (movedOutOfTheWindow)
            {
                VerticalShift();
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

    //////////////////////////////////////////////////////////////////////////////
    
    Environment::Environment()
    {
        static constexpr int initialCapacity = 10;
        pipes.reserve(initialCapacity);

        pipes.push_back(std::make_unique<Pipes>());

        for (int i = 1; i < initialCapacity; i++)
            pipes.push_back(std::make_unique<Pipes>( pipes[i - 1]->GetPipesSegment()[0].GetPosition().x 
                                                   + pipes[i - 1]->GetPipesSegment()[0].GetSize().x
                                                   + horizontalDistanceBetweenPipes ));
    }

    void Environment::UpdateState()
    {
        float theFurthestPipePositionX = pipes[0]->GetPipesSegment()[0].GetPosition().x;
        
        for (auto& pipeSegment : pipes)
        {
            pipeSegment->UpdateState();

            if (theFurthestPipePositionX < pipeSegment->GetPipesSegment()[0].GetPosition().x)
                theFurthestPipePositionX = pipeSegment->GetPipesSegment()[0].GetPosition().x;
        }

        for (auto& pipeSegment : pipes)
        {
            const bool movedOutOfTheWindow = pipeSegment->GetPipesSegment()[0].MovedOutOfTheWindow();
            if (movedOutOfTheWindow)
                theFurthestPipePositionX += pipeSegment->GetPipesSegment()[0].GetSize().x + horizontalDistanceBetweenPipes;
            
            pipeSegment->ResetPosition(movedOutOfTheWindow, theFurthestPipePositionX);
        }
    }

    std::span<const std::unique_ptr<Pipes>> Environment::GetPipes() const
    {
        return this->pipes;
    }
}

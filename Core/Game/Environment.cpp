#include "Game/Environment.hpp"

namespace Game
{
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
        if (isStopped)
            return;

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

    void Environment::Stop()
    {
        isStopped = true;
    }
}

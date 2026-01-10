#include "GameUtils.hpp"

#include "Bird.hpp"
#include "Pipes.hpp"

namespace Game
{
    float CalculateXDistance(const Bird& bird, const std::unique_ptr<Game::Pipes>& pipes)
    {
        const float pipesXPosition = pipes->GetPipesSegment().begin()->GetPosition().x;
        return pipesXPosition - bird.GetPosition().x;
    }

    float CalculateXDistance(const Bird& bird, const Game::Pipes& pipes)
    {
        const float pipesXPosition = pipes.GetPipesSegment().begin()->GetPosition().x;
        return pipesXPosition - bird.GetPosition().x;
    }
}
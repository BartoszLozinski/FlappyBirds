#include "GameUtils.hpp"

namespace Game
{
    float CalculateXDsitance(const Bird& bird, const std::unique_ptr<Game::Pipes>& pipes)
    {
        const float pipesXPosition = pipes->GetPipesSegment().begin()->GetPosition().x;
        return pipesXPosition - bird.GetPosition().x;
    }

    float CalculateXDsitance(const Bird& bird, const Game::Pipes& pipes)
    {
        const float pipesXPosition = pipes.GetPipesSegment().begin()->GetPosition().x;
        return pipesXPosition - bird.GetPosition().x;
    }
}
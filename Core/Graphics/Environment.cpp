#include "Environment.hpp"

namespace Graphics
{
    Environment::Environment(const Game::Environment& environment_)
        : environment(environment_)
    {
        pipesRenderable.reserve(environment.GetPipes().size());
        
        for (auto& pipesSegment : environment.GetPipes())
            pipesRenderable.push_back(*pipesSegment);
    }

    void Environment::UpdatePosition()
    {
        for (auto& pipesSegment : pipesRenderable)
            pipesSegment.UpdatePosition();
    }

    void Environment::Draw(sf::RenderTarget& target) const
    {
        for (auto& pipes : pipesRenderable)
            pipes.Draw(target);
    }
}
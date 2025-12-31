#include "Graphics/Pipes.hpp"

namespace Graphics
{
    Pipes::Pipes(const Game::Pipes& pipesSegment_)
        : pipesSegment(pipesSegment_)
        , pipesRenderable( { Rectangle{ pipesSegment.GetPipesSegment()[0] }
                           , Rectangle{ pipesSegment.GetPipesSegment()[1] }})
        {}

    void Pipes::UpdatePosition()
    {
        for (auto& pipe : pipesRenderable)
        {
            pipe.UpdatePosition();
        }
    }

    void Pipes::Draw(sf::RenderWindow& window) const
    {
        for (auto& pipe : pipesRenderable)
        {
            pipe.Draw(window);
        }
    }

    ///////////////////////////////////////////

    PipesManager::PipesManager(const Game::PipesManager& pipesManager_)
        : pipesManager(pipesManager_)
    {
        pipesRenderable.reserve(pipesManager.GetPipes().size());
        
        for (auto& pipesSegment : pipesManager.GetPipes())
            pipesRenderable.push_back(*pipesSegment);
    }

    void PipesManager::UpdatePosition()
    {
        for (auto& pipesSegment : pipesRenderable)
            pipesSegment.UpdatePosition();
    }

    void PipesManager::Draw(sf::RenderWindow& window) const
    {
        for (auto& pipes : pipesRenderable)
            pipes.Draw(window);
    }
};
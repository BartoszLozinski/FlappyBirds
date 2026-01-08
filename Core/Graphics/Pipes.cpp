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
};
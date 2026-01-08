#pragma once

#include "Game/Pipes.hpp"
#include "Rectangle.hpp"

namespace Graphics
{
    class Pipes
    {
    private:
        const Game::Pipes& pipesSegment;
        std::array<Rectangle, 2> pipesRenderable;

    public:
        Pipes(const Game::Pipes& pipesSegment_);
        
        void UpdatePosition();
        void Draw(sf::RenderWindow& window) const;
    };
}
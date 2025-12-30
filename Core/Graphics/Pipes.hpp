#pragma once

#include "Rectangle.hpp"
#include "Game/Pipes.hpp"

namespace Graphics
{
    class Pipes
    {
    private:
        const Game::Pipes& pipes;
        std::array<Rectangle, 2> pipesRenderable;

    public:
        Pipes(const Game::Pipes& pipes_);
        
        void UpdatePosition();
        void Draw(sf::RenderWindow& window) const;
    };
}
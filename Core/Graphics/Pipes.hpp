#pragma once

#include "Rectangle.hpp"
#include "Game/Pipes.hpp"

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

    class PipesManager
    {
    private:
        const Game::Environment& pipesManager;
        std::vector<Graphics::Pipes> pipesRenderable;

    public:
        PipesManager(const Game::Environment& pipesManager_);
        void UpdatePosition();
        void Draw(sf::RenderWindow& window) const;
    
    };
}
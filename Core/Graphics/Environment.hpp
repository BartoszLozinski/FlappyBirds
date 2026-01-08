#pragma once

#include "Game/Environment.hpp"

#include "Graphics/Pipes.hpp"

namespace Graphics
{
    class Environment
    {
    private:
        const Game::Environment& environment;
        std::vector<Graphics::Pipes> pipesRenderable;

    public:
        Environment(const Game::Environment& environment_);
        void UpdatePosition();
        void Draw(sf::RenderWindow& window) const;
    
    };
}
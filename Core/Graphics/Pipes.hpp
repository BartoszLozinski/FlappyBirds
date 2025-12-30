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
        void UpdatePosition();

    public:
        Pipes(const Game::Pipes& pipes_);

    };
}
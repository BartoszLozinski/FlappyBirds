#pragma once

namespace Gameplay
{
    struct State
    {
        float birdX{}; //center position
        float birdY{};
        unsigned birdSize{};
        float birdVy{};
        float nextPipeX{};
        float topPipeY{};   //center position
        float bottomPipeY{}; 
        unsigned pipeSizeX{};
        unsigned pipesSizeY{};
        unsigned pipesGapY{};
        bool birdAbleToJump{};
        unsigned framesSinceLastJump{};
        bool birdAlive{};
    };
}
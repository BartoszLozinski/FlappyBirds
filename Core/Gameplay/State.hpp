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
        float gapTopVertexY{};   //center position
        float gapBottomVertexY{}; 
        bool birdAbleToJump{};
        unsigned framesSinceLastJump{};
        bool birdAlive{};
    };
}
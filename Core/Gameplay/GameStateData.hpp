#pragma once

#include <cstdint>

#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

class GameStateData
{
private:
    uint64_t frameIdx{};
    float birdX{}; //center position
    float birdY{};
    float birdVy{};
    float dxNextPipe{};
    float nextPipeX{};
    float topPipeY{};   //center position
    float bottomPipeY{}; 
    unsigned pipeSize{};
    bool birdAbleToJump{};
    unsigned framesSinceLastJump{};
    bool birdAlive{};
    unsigned points{};
    int action{}; // 0 = None, 1 = Jump
public:
    GameStateData() = default;
    void SetState(uint64_t frameIdx_, const Game::Bird& bird, const Game::Pipes& pipes);
};
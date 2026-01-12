#pragma once

#include <cstdint>

#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

class DataProvider
{
private:
    float birdX{}; //center position
    float birdY{};
    unsigned birdSize{};
    float birdVy{};
    float nextPipeX{};
    float topPipeY{};   //center position
    float bottomPipeY{}; 
    unsigned pipeSizeX{};
    unsigned pipesSizeY{};
    bool birdAbleToJump{};
    unsigned framesSinceLastJump{};
    bool birdAlive{};
    unsigned points{};
    int action{}; // 0 = None, 1 = Jump
public:

    DataProvider() = default;
    void SetState(const Game::Bird& bird, const Game::Pipes& pipes, const ControlOption controlOption);
    std::string GetRow() const;
    std::string GetHeader() const;
};
#pragma once

#include <cstdint>

#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

struct GameplayState
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

class DataProvider
{
private:
    GameplayState gameplayState{};

public:

    DataProvider() = default;
    void SetState(const Game::Bird& bird, const Game::Pipes& pipes);
    std::string GetRow() const;
    GameplayState GetGameplayState() const;
    std::string GetHeader() const;
};
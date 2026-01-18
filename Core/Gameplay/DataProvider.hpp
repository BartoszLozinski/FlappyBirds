#pragma once

#include <cstdint>

#include "Gameplay/GameplayState.hpp"

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
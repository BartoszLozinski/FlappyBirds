#pragma once

#include <cstdint>

#include "Gameplay/GameplayState.hpp"

namespace Gameplay
{
    class DataProvider
    {
    private:
        State gameplayState{};

    public:

        DataProvider() = default;
        void SetState(const Game::Bird& bird, const Game::Pipes& pipes);
        std::string GetRow() const;
        State GetGameplayState() const;
        std::string GetHeader() const;
    };
}
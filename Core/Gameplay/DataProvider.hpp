#pragma once

#include <cstdint>

#include "State.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

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
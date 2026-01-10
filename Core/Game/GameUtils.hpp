#pragma once

#include "Bird.hpp"
#include "Pipes.hpp"

namespace Game
{
    [[nodiscard]] float CalculateXDsitance(const Bird& bird, const std::unique_ptr<Game::Pipes>& pipes);
    [[nodiscard]] float CalculateXDsitance(const Bird& bird, const Game::Pipes& pipes);
}
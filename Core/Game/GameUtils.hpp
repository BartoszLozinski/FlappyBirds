#pragma once

#include <memory>

namespace Game
{
    class Bird;
    class Pipes;

    [[nodiscard]] float CalculateXDistance(const Bird& bird, const std::unique_ptr<Game::Pipes>& pipes);
    [[nodiscard]] float CalculateXDistance(const Bird& bird, const Game::Pipes& pipes);
}
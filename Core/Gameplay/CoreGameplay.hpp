#pragma once

#include "Game/GameConfig.hpp"
#include "Game/Timer.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"
#include <optional>

class CoreGameplay
{
private:
    bool frameTimeExpired = false;

protected:
    Bird bird{ Utils::Vector2u{20, 20}, Utils::Vector2f{200, 300} };
    Game::PipesManager pipesManager{};
    Timer frameTimer{1000 / 60};

    float CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const;
    float CalculateXDsitance(const Game::Pipes& pipes) const;
    const Game::Pipes& GetClosestPipes() const;
    std::optional<std::reference_wrapper<const Game::Pipes>> GetClosestPipesBehind() const;
    void UpdateState();
    void UpdatePoints(const Utils::Vector2f& closestPipesPositionBeforeUpdateState, const Game::Pipes& closestPipes);
    bool FrameTimeExpired() const;
    bool CheckCollisionWithPipesSegment(const Game::Pipes& pipes) const;

public:
    unsigned GetPoints() const;
    void RunFrame(const ControlOption ControlOption);
    bool CheckCollision(const std::optional<std::reference_wrapper<const Game::Pipes>> pipesBehind, const Game::Pipes& pipesInFront) const;
};

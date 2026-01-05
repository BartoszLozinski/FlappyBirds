#pragma once

#include "Game/GameConfig.hpp"
#include "Game/Timer.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

class CoreGameplay
{
private:
    bool frameTimeExpired = false;

protected:
    Bird bird{ Utils::Vector2u{20, 20}, Utils::Vector2f{200, 300} };
    Game::PipesManager pipesManager{};
    Timer frameTimer{1000 / 60};
    unsigned points = 0;

    float CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const;
    float CalculateXDsitance(const Game::Pipes& pipes) const;
    Game::Pipes& GetClosestPipes() const;
    void UpdateState();
    void UpdatePoints(const Utils::Vector2f& closestPipesPositionBeforeUpdateState, const Game::Pipes& closestPipes);
    bool FrameTimeExpired() const;

public:
    unsigned GetPoints() const;
    void RunFrame(const ControlOption ControlOption);
};

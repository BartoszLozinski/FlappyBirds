#pragma once

#include "Game/GameConfig.hpp"
#include "Game/Timer.hpp"
#include "Game/Bird.hpp"
#include "Game/Environment.hpp"
#include <optional>

class CoreGameplay
{
private:
    bool frameTimeExpired = false;

    enum class PipesDirection
    {
        InFront,
        Behind,
    };

protected:
    Game::Bird bird{};
    std::shared_ptr<Game::Environment> environment = std::make_shared<Game::Environment>();
    Game::Timer frameTimer{1000 / 60};

    float CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const;
    float CalculateXDsitance(const Game::Pipes& pipes) const;

    template <PipesDirection direction>
    std::optional<std::reference_wrapper<Game::Pipes>> GetClosestPipes() const
    {
        const auto& pipes = environment->GetPipes();
        auto closestPipes = pipes.end();

        for (auto currentPipes = pipes.begin(); currentPipes != pipes.end(); currentPipes++)
        {
            const float xDistance = CalculateXDsitance(*currentPipes);

            if constexpr (direction == PipesDirection::InFront)
            {
                if (xDistance >= 0 && (closestPipes == pipes.end() || xDistance < CalculateXDsitance(*closestPipes)))
                    closestPipes = currentPipes;
            }
            else
            {
                if (xDistance <= 0 && (closestPipes == pipes.end() || xDistance > CalculateXDsitance(*closestPipes)))
                    closestPipes = currentPipes;
            }
        }

        if (closestPipes == pipes.end())
            return std::nullopt;
        else
            return std::make_optional(std::ref(*closestPipes->get()));
    }

    void UpdatePoints(std::optional<std::reference_wrapper<Game::Pipes>> closestPipeBehind);
    bool FrameTimeExpired() const;
    bool CheckCollisionWithPipesSegment(const std::optional<std::reference_wrapper<Game::Pipes>> pipes) const;

public:
    unsigned GetPoints() const;
    void RunFrame(const ControlOption ControlOption);
    bool CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const std::optional<std::reference_wrapper<Game::Pipes>> pipesInFront) const;
};

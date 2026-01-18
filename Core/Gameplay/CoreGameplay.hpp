#pragma once

#include "Game/GameUtils.hpp"
#include "Game/GameConfig.hpp"
#include "Gameplay/Timer.hpp"
#include "Game/Bird.hpp"
#include "Game/Environment.hpp"
#include "Gameplay/State.hpp"
#include "Gameplay/Event.hpp"
#include <optional>

namespace Gameplay
{
    class CoreLogic
    {
    private:
        enum class PipesDirection
        {
            InFront,
            Behind,
        };

    protected:
        Game::Bird bird{};
        std::shared_ptr<Game::Environment> environment = std::make_shared<Game::Environment>();

        template <PipesDirection direction>
        std::optional<std::reference_wrapper<Game::Pipes>> GetClosestPipes() const
        {
            const auto& pipes = environment->GetPipes();
            auto closestPipes = pipes.end();

            for (auto currentPipes = pipes.begin(); currentPipes != pipes.end(); currentPipes++)
            {
                const float xDistance = Game::CalculateXDistance(bird, *currentPipes);

                if constexpr (direction == PipesDirection::InFront)
                {
                    if (xDistance >= 0 && (closestPipes == pipes.end() || xDistance < Game::CalculateXDistance(bird, *closestPipes)))
                        closestPipes = currentPipes;
                }
                else
                {
                    if (xDistance <= 0 && (closestPipes == pipes.end() || xDistance > Game::CalculateXDistance(bird, *closestPipes)))
                        closestPipes = currentPipes;
                }
            }

            if (closestPipes == pipes.end())
                return std::nullopt;
            else
                return std::make_optional(std::ref(*closestPipes->get()));
        }

        [[nodiscard]] bool UpdatePoints(std::optional<std::reference_wrapper<Game::Pipes>> closestPipeBehind);
        bool CheckCollisionWithPipesSegment(const std::optional<std::reference_wrapper<Game::Pipes>> pipes) const;

    public:
        bool CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const std::optional<std::reference_wrapper<Game::Pipes>> pipesInFront) const;
        State GetState() const;
        unsigned GetPoints() const;
        void Reset();
        Event RunFrame(const ControlOption ControlOption, const bool frameTimeExpired);

    };
}

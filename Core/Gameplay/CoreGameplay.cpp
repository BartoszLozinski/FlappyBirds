#include "CoreGameplay.hpp"

#include <assert.h>
#include <algorithm>
#include <ranges>
#include <functional>

#include "Game/Collision.hpp"
#include <iostream>

float CoreGameplay::CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const
{
    const float pipesXPosition = pipes->GetPipesSegment().begin()->GetPosition().x;
    return pipesXPosition - bird.GetPosition().x;
}

float CoreGameplay::CalculateXDsitance(const Game::Pipes& pipes) const
{
    const float pipesXPosition = pipes.GetPipesSegment().begin()->GetPosition().x;
    return pipesXPosition - bird.GetPosition().x;
}

bool CoreGameplay::FrameTimeExpired() const
{
    return frameTimeExpired;
}

unsigned CoreGameplay::GetPoints() const
{
    return bird.GetPoints();
}

void CoreGameplay::UpdatePoints(std::optional<std::reference_wrapper<Game::Pipes>> closestPipeBehind)
{
    if (closestPipeBehind
        && !closestPipeBehind->get().IsScored()
        && closestPipeBehind->get().GetPipesSegment()[0].GetPosition().x < bird.GetPosition().x)
    {
        ++bird;
        closestPipeBehind->get().Score();
    }
}

void CoreGameplay::RunFrame(const ControlOption controlOption)
{
    frameTimeExpired = false;

    bird.Control(controlOption);

    if (frameTimer.IsExpired())
    {
        bird.UpdateState();
        pipesManager->UpdateState();

        if (CheckCollision(GetClosestPipes<PipesDirection::Behind>(), GetClosestPipes<PipesDirection::InFront>()))
            bird.Kill();

        UpdatePoints(GetClosestPipes<PipesDirection::Behind>());
        frameTimer.Reset();

        frameTimeExpired = true;
    }
}

bool CoreGameplay::CheckCollisionWithPipesSegment(const std::optional<std::reference_wrapper<Game::Pipes>> pipes) const
{
    return std::ranges::any_of(pipes->get().GetPipesSegment(), [&](const auto& pipe)
        { 
            return Collision::AABB(bird, pipe);
        });
}

bool CoreGameplay::CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const std::optional<std::reference_wrapper<Game::Pipes>>  pipesInFront) const
{
    bool result = CheckCollisionWithPipesSegment(pipesInFront);
    if (pipesBehind)
        result |= CheckCollisionWithPipesSegment(pipesBehind);
   
    return result;
}
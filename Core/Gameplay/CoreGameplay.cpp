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

const Game::Pipes& CoreGameplay::GetClosestPipes() const
{
    const auto& pipes = pipesManager.GetPipes();
    Game::Pipes* closestPipe = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& pipe : pipes)
    {
        const float xDistance = CalculateXDsitance(*pipe);

        if (xDistance >= 0 && xDistance < minDistance)
        {
            minDistance = xDistance;
            closestPipe = pipe.get();
        }
    }

    assert(closestPipe != nullptr);
    return *closestPipe;
}

std::optional<std::reference_wrapper<Game::Pipes>> CoreGameplay::GetClosestPipesBehind() const
{
    const auto& pipes = pipesManager.GetPipes();
    auto closestPipes = pipes.end();

    for (auto currentPipe = pipes.begin(); currentPipe != pipes.end(); currentPipe++)
    {
        const float xDistance = CalculateXDsitance(*currentPipe);

        if (xDistance <= 0 &&
            (closestPipes == pipes.end() || xDistance > CalculateXDsitance(*closestPipes)))
        {
            closestPipes = currentPipe;
        }
    }

    if (closestPipes == pipes.end())
        return std::nullopt;
    else
        return std::make_optional(std::ref(*closestPipes->get()));
}

unsigned CoreGameplay::GetPoints() const
{
    return bird.GetPoints();
}

void CoreGameplay::UpdateState()
{
    bird.UpdateState();
    pipesManager.UpdateState();
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

        UpdateState();
        if (CheckCollision(GetClosestPipesBehind(), GetClosestPipes()))
            bird.Kill();

        UpdatePoints(GetClosestPipesBehind());
        frameTimer.Reset();

        frameTimeExpired = true;
    }
}

bool CoreGameplay::CheckCollisionWithPipesSegment(const Game::Pipes& pipes) const
{
    return std::ranges::any_of(pipes.GetPipesSegment(), [&](const auto& pipe)
        { 
            return Collision::AABB(bird, pipe);
        });
}

bool CoreGameplay::CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const Game::Pipes& pipesInFront) const
{
    bool result = CheckCollisionWithPipesSegment(pipesInFront);
    if (pipesBehind)
        result |= CheckCollisionWithPipesSegment(pipesBehind->get());
   
    return result;
}
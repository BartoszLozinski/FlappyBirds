#include "CoreGameplay.hpp"

#include <assert.h>
#include <algorithm>
#include <ranges>
#include <functional>

#include "Game/Collision.hpp"

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
    auto closestPipes = pipes.end();
    auto currentPipe = pipes.begin();

    while(currentPipe != pipes.end())
    {
        const float xDistance = CalculateXDsitance(*currentPipe);

        if (xDistance >= 0 &&
            (closestPipes == pipes.end() || xDistance < CalculateXDsitance(*closestPipes)))
        {
            closestPipes = currentPipe;
        }

        currentPipe++;
    }

    assert(closestPipes != pipes.end());
    return *closestPipes->get();
}

std::optional<std::reference_wrapper<const Game::Pipes>> CoreGameplay::GetClosestPipesBehind() const
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

void CoreGameplay::UpdatePoints(const Utils::Vector2f& closestPipesPositionBeforeUpdateState, const Game::Pipes& closestPipes)
{
    const auto birdPosition = bird.GetPosition();
    if (closestPipesPositionBeforeUpdateState.x >= birdPosition.x && CalculateXDsitance(closestPipes) <= 0.0f)
        ++bird;
}

void CoreGameplay::RunFrame(const ControlOption controlOption)
{
    frameTimeExpired = false;

    bird.Control(controlOption);

    if (frameTimer.IsExpired())
    {
        const auto closestPipesPositionBeforeUpdateState = GetClosestPipes().GetPipesSegment()[0].GetPosition();

        UpdateState();
        const auto& closestPipes = GetClosestPipes();
        if (CheckCollision(GetClosestPipesBehind(), closestPipes))
            bird.Kill();

        UpdatePoints(closestPipesPositionBeforeUpdateState, closestPipes);

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

bool CoreGameplay::CheckCollision(std::optional<std::reference_wrapper<const Game::Pipes>> pipesBehind, const Game::Pipes& pipesInFront) const
{
    bool result = CheckCollisionWithPipesSegment(pipesInFront);
    if (pipesBehind)
        result |= CheckCollisionWithPipesSegment(pipesBehind->get());
   
    return result;
}
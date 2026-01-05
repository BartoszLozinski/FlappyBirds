#include "CoreGameplay.hpp"

#include <assert.h>


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

Game::Pipes& CoreGameplay::GetClosestPipes() const
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

unsigned CoreGameplay::GetPoints() const
{
    return points;
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
        points++;
}

void CoreGameplay::RunFrame(const ControlOption controlOption)
{
    frameTimeExpired = false;
    bird.Control(controlOption);

    if (frameTimer.IsExpired())
    {
        const auto& closestPipes = GetClosestPipes();
        const auto closestPipesPositionBeforeUpdateState = closestPipes.GetPipesSegment()[0].GetPosition();

        UpdateState();
        UpdatePoints(closestPipesPositionBeforeUpdateState, closestPipes);

        //Display();

        frameTimer.Reset();
        frameTimeExpired = true;
        //keyboardController.ResetState();
    }
}
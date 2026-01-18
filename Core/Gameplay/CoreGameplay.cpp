#include "CoreGameplay.hpp"

#include <assert.h>
#include <algorithm>
#include <ranges>
#include <functional>

#include "Game/Collision.hpp"
#include <iostream>

bool CoreGameplay::CheckCollisionWithPipesSegment(const std::optional<std::reference_wrapper<Game::Pipes>> pipes) const
{
    return std::ranges::any_of(pipes->get().GetPipesSegment(), [&](const auto& pipe)
        { 
            return Game::Collision::AABB(bird, pipe);
        });
}

bool CoreGameplay::CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const std::optional<std::reference_wrapper<Game::Pipes>>  pipesInFront) const
{
    bool result = CheckCollisionWithPipesSegment(pipesInFront);
    if (pipesBehind)
        result |= CheckCollisionWithPipesSegment(pipesBehind);
   
    return result;
}

/*
bool CoreGameplay::FrameTimeExpired() const
{
    return frameTimeExpired;
}
*/

unsigned CoreGameplay::GetPoints() const
{
    return bird.GetPoints();
}

/*

struct GameplayState
{
    float birdX{}; //center position
    float birdY{};
    unsigned birdSize{};
    float birdVy{};
    float nextPipeX{};
    float topPipeY{};   //center position
    float bottomPipeY{}; 
    unsigned pipeSizeX{};
    unsigned pipesSizeY{};
    unsigned pipesGapY{};
    bool birdAbleToJump{};
    unsigned framesSinceLastJump{};
    bool birdAlive{};
};

*/

GameplayState CoreGameplay::GetState() const
{
    GameplayState state{};

    const auto& birdPosition = bird.GetPosition();
    state.birdX = birdPosition.x;
    state.birdY = birdPosition.y;
    state.birdSize = bird.GetSize().x; //bounding box for circle, so one dimension
    state.birdVy = bird.GetVelocity().y;

    const auto& closestPipes = GetClosestPipes<PipesDirection::InFront>();
    if (closestPipes)
    {
        const auto& pipesSegment = closestPipes->get().GetPipesSegment();
        state.nextPipeX = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Top)].GetPosition().x;
        state.topPipeY = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Top)].GetPosition().y;
        state.bottomPipeY = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Bottom)].GetPosition().x;
        state.pipeSizeX = state.nextPipeX = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Top)].GetSize().x;
        state.pipesSizeY = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Top)].GetSize().x;
        state.pipesGapY = Game::Pipes::verticalDistanceBetweenPipes;
        state.birdAbleToJump = bird.IsAbleToJump();
        state.framesSinceLastJump = bird.GetFramesSinceLastJump();
        state.birdAlive = bird.IsAlive();
    }

    return state;
}

void CoreGameplay::RunFrame(const ControlOption controlOption, const bool frameTimeExpired)
{
    //frameTimeExpired = false;

    bird.Control(controlOption);

    //if (frameTimer.IsExpired())
    if (frameTimeExpired)
    {
        bird.UpdateState();
        environment->UpdateState();

        if (CheckCollision(GetClosestPipes<PipesDirection::Behind>(), GetClosestPipes<PipesDirection::InFront>()))
            bird.Kill();

        if (!bird.IsAlive())
            environment->Stop();

        UpdatePoints(GetClosestPipes<PipesDirection::Behind>());
        //frameTimer.Reset();

        //frameTimeExpired = true;
    }
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

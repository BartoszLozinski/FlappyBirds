#include "CoreGameplay.hpp"

#include <assert.h>
#include <algorithm>
#include <ranges>
#include <functional>

#include "Game/Collision.hpp"
#include <iostream>

namespace Gameplay
{

    bool CoreLogic::CheckCollisionWithPipesSegment(const std::optional<std::reference_wrapper<Game::Pipes>> pipes) const
    {
        return std::ranges::any_of(pipes->get().GetPipesSegment(), [&](const auto& pipe)
            { 
                return Game::Collision::AABB(bird, pipe);
            });
    }

    bool CoreLogic::CheckCollision(const std::optional<std::reference_wrapper<Game::Pipes>> pipesBehind, const std::optional<std::reference_wrapper<Game::Pipes>>  pipesInFront) const
    {
        bool result = CheckCollisionWithPipesSegment(pipesInFront);
        if (pipesBehind)
            result |= CheckCollisionWithPipesSegment(pipesBehind);
    
        return result;
    }

    unsigned CoreLogic::GetPoints() const
    {
        return bird.GetPoints();
    }

    State CoreLogic::GetState() const
    {
        State state{};

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
            state.pipeSizeY = pipesSegment[static_cast<std::size_t>(Game::PipesSegmentIndex::Top)].GetSize().x;
            state.pipesGapY = Game::Pipes::verticalDistanceBetweenPipes;
            state.birdAbleToJump = bird.IsAbleToJump();
            state.framesSinceLastJump = bird.GetFramesSinceLastJump();
            state.birdAlive = bird.IsAlive();
        }

        return state;
    }

    void CoreLogic::Reset()
    {
        bird = Game::Bird{};
        environment =std::make_shared<Game::Environment>();
    }

    Event CoreLogic::RunFrame(const ControlOption controlOption, const bool frameTimeExpired)
    {
        Event event{};

        bird.Control(controlOption);

        if (!frameTimeExpired)
            return event;

        event.frameAdvanced = true;

        if (CheckCollision(GetClosestPipes<PipesDirection::Behind>(), GetClosestPipes<PipesDirection::InFront>()))
        {
            bird.Kill();
            event.birdDied = true;
        }

        bird.UpdateState();
        environment->UpdateState();

        if (UpdatePoints(GetClosestPipes<PipesDirection::Behind>()))
            event.pipePassed = true;

        return event;        
    }

    bool CoreLogic::UpdatePoints(std::optional<std::reference_wrapper<Game::Pipes>> closestPipeBehind)
    {
        if (closestPipeBehind
            && !closestPipeBehind->get().IsScored()
            && closestPipeBehind->get().GetPipesSegment()[0].GetPosition().x < bird.GetPosition().x)
        {
            ++bird;
            closestPipeBehind->get().Score();
            return true;
        }

        return false;
    }
}

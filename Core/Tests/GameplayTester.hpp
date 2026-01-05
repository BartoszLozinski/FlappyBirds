#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gameplay/Gameplay.hpp"

class GameplayDummy : public Gameplay
{
public:
    void UpdatePointsAPI(const Utils::Vector2f& closestPipesPositionBeforeUpdateState, const Game::Pipes& closestPipes)
    {
        UpdatePoints(closestPipesPositionBeforeUpdateState, closestPipes);
    }
};

class GameplayFixutre : public testing::Test
{
public:
    GameplayDummy gameplayFixture{};
};

TEST_F(GameplayFixutre, PointAddedTest)
{
    Game::Pipes gamePipes{201.f}; //bird initial position is {200, 300}
    const float initialPoints = gameplayFixture.GetPoints();
    const Utils::Vector2f initialPipesPosition = gamePipes.GetPipesSegment().begin()->GetPosition();

    gamePipes.UpdateState();
    
    gameplayFixture.UpdatePointsAPI(initialPipesPosition, gamePipes);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints + 1);
}

TEST_F(GameplayFixutre, PointNotAddedTest)
{
    Game::Pipes gamePipes{205.f}; //bird initial position is {200, 300}
    const float initialPoints = gameplayFixture.GetPoints();
    const Utils::Vector2f initialPipesPosition = gamePipes.GetPipesSegment().begin()->GetPosition();

    gamePipes.UpdateState();
    
    gameplayFixture.UpdatePointsAPI(initialPipesPosition, gamePipes);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints);
}

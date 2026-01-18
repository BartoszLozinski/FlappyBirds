#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gameplay/CoreGameplay.hpp"

class GameplayDummy : public Gameplay::CoreLogic
{
public:
    bool UpdatePointsAPI(std::optional<std::reference_wrapper<Game::Pipes>> closestPipeBehind)
    {
        return UpdatePoints(closestPipeBehind);
    }
};

class GameplayFixutre : public testing::Test
{
public:
    GameplayDummy gameplayFixture{};
};

TEST_F(GameplayFixutre, PointAddedTest)
{
    //bird initial position is {200, 300}
    auto gamePipes = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(199.f)));
    const float initialPoints = gameplayFixture.GetPoints();

    gamePipes->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(gamePipes);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints + 1);
}

TEST_F(GameplayFixutre, PointNotAddedTest)
{
    auto pipesBehind = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(205.f)));

    const float initialPoints = gameplayFixture.GetPoints();

    pipesBehind->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(pipesBehind);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints);
}

TEST_F(GameplayFixutre, PointNotAddedTestBecauseScored)
{
    auto pipesBehind = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(199.f)));
    const float initialPoints = gameplayFixture.GetPoints();

    pipesBehind->get().Score();
    pipesBehind->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(pipesBehind);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints);
}

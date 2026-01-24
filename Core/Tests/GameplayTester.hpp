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
    static constexpr float initialXPosition = 199.f;
    auto gamePipes = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(80, 500, initialXPosition, -50, 650)));
    const float initialPoints = gameplayFixture.GetPoints();

    gamePipes->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(gamePipes);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints + 1);
}

TEST_F(GameplayFixutre, PointNotAddedTest)
{
    static constexpr float initialXPosition = 205.f;
    auto pipesBehind = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(80, 500, initialXPosition, -50, 650)));

    const float initialPoints = gameplayFixture.GetPoints();

    pipesBehind->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(pipesBehind);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints);
}

TEST_F(GameplayFixutre, PointNotAddedTestBecauseScored)
{
    static constexpr float initialXPosition = 199.f;
    auto pipesBehind = std::make_optional<std::reference_wrapper<Game::Pipes>>(std::ref(*std::make_unique<Game::Pipes>(80, 500, initialXPosition, -50, 650)));
    const float initialPoints = gameplayFixture.GetPoints();

    pipesBehind->get().Score();
    pipesBehind->get().UpdateState();
    
    gameplayFixture.UpdatePointsAPI(pipesBehind);

    ASSERT_EQ(gameplayFixture.GetPoints(), initialPoints);
}

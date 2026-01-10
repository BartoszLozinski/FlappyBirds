#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/GameUtils.hpp"

TEST(CalculateXDistanceTest, distance100Expected)
{
    Game::Bird bird{ Utils::Vector2u{10, 10}, Utils::Vector2f{100, 100} };
    Game::Pipes pipes{ 200.f };
    constexpr auto expectedDistance = 100.f;

    const auto result = Game::CalculateXDsitance(bird, pipes);

    ASSERT_EQ(result, expectedDistance);
};
#pragma once

#include <tuple>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/Collision.hpp"

class EntityDummy : public Entity
{
public:
    EntityDummy(const Utils::Vector2f& position_) : Entity({10, 10}, position_) {};

    void UpdateState() override { return; }
    void SetPosition(const Utils::Vector2f& position_) { this->position = position_; }
};

class EntityFixutre : public testing::TestWithParam<std::tuple<Utils::Vector2f, bool>>
{
public:
    EntityDummy entityDummy{{100.f, 100.f}};
};

TEST_P(EntityFixutre, CollisionAABBTest)
{
    auto [positionParam, result] = GetParam();
    EntityDummy secondEntity{positionParam};

    ASSERT_EQ(Collision::AABB(entityDummy, secondEntity), result);
}

INSTANTIATE_TEST_SUITE_P(CollisionAABBTestParams, EntityFixutre, testing::Values(
    std::make_tuple(Utils::Vector2f{130, 100}, false),
    std::make_tuple(Utils::Vector2f{90, 90}, true), //left top corner
    std::make_tuple(Utils::Vector2f{110, 90}, true), //right top corner
    std::make_tuple(Utils::Vector2f{90, 110}, true), //left bottom corner
    std::make_tuple(Utils::Vector2f{110, 110}, true), //right bottom corner
    std::make_tuple(Utils::Vector2f{95, 95}, true)) //intersecting
);

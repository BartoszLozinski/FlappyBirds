#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/Bird.hpp"

class BirdDummy : public Game::Bird
{
public:
   BirdDummy(const Utils::Vector2u& size_, const Utils::Vector2f& position_)
        : Bird(size_, position_){}; 

    inline void SetAbleToJump() { this->framesSinceLastJump = this->FRAMES_TO_RESET_JUMP_ABILITY; }
    inline void SetUnableToJump() { this->framesSinceLastJump = 0; };
    inline ControlOption GetControlOption() const { return this->currentControlOption; };
};

struct BirdFixture : public testing::Test
{
    BirdDummy birdFixture{{20, 20}, {30.f, 30.f}};

    void SetUp() override;
};

TEST_F(BirdFixture, FreeFallTest)
{
    const auto oldPosition = birdFixture.GetPosition();
    birdFixture.UpdateState();
    ASSERT_GT(birdFixture.GetPosition().y, oldPosition.y);
}

TEST_F(BirdFixture, JumpTest)
{
    const auto oldPosition = birdFixture.GetPosition();
    const auto oldVelocity = birdFixture.GetVelocity();

    birdFixture.Control(ControlOption::Jump);
    birdFixture.UpdateState();

    ASSERT_LT(birdFixture.GetPosition().y, oldPosition.y);
    ASSERT_LT(birdFixture.GetVelocity().y, oldVelocity.y);
    ASSERT_EQ(birdFixture.GetControlOption(), ControlOption::None);
}

void BirdFixture::SetUp()
{
    birdFixture.SetAbleToJump();
}

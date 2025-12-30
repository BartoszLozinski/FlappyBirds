#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Game/Bird.hpp"

struct BirdFixture : public testing::Test
{
    Bird bird{{10, 10}, {20, 20}};
};


TEST_F(BirdFixture, FreeFallTest)
{
    Bird bird{{10, 10}, {20, 20}};
    const auto oldPosition = bird.GetPosition();
    bird.UpdateState();
    ASSERT_GT(bird.GetPosition().y, oldPosition.y);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

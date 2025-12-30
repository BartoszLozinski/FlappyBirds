#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Game/Bird.hpp"

TEST(JustTest, compilationTest)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

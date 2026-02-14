#include "BirdTester.hpp"
#include "CollisionTester.hpp"
#include "GameUtilsTester.hpp"
#include "GameplayTester.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

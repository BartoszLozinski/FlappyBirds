#include "CoreLogicAdapter.hpp"

CoreLogicAdapter::CoreLogicAdapter(std::shared_ptr<Game::Environment> gameEnvPtr)
{
    SetEnvironment(gameEnvPtr);
};

void CoreLogicAdapter::SetEnvironment(std::shared_ptr<Game::Environment> gameEnvPtr)
{
    if (gameEnvPtr)
        environment = gameEnvPtr;
}
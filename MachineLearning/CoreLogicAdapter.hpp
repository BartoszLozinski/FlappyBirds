#include "Gameplay/CoreGameplay.hpp"

class CoreLogicAdapter : public Gameplay::CoreLogic
{
public:
    CoreLogicAdapter(std::shared_ptr<Game::Environment> gameEnvPtr);
    void SetEnvironment(std::shared_ptr<Game::Environment> gameEnvPtr);
};

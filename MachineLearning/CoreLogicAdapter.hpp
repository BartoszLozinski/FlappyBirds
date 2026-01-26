#include "Gameplay/CoreGameplay.hpp"

namespace ReinforcementLearning
{
    class EnvironmentAdapter : public Game::Environment
    {
    public:
        EnvironmentAdapter(const unsigned seed);
        EnvironmentAdapter(const EnvironmentAdapter& other);
        EnvironmentAdapter(EnvironmentAdapter&& other);

        void Seed(const unsigned seed);
    };

    class CoreLogicAdapter : public Gameplay::CoreLogic
    {
    protected:
        std::shared_ptr<EnvironmentAdapter> envAdapter = nullptr;
    public:
        CoreLogicAdapter(std::shared_ptr<EnvironmentAdapter> gameEnvAdapterPtr);
        void SetEnvironment(std::shared_ptr<EnvironmentAdapter> gameEnvAdapterPtr);
        void Seed(const unsigned seed);
        std::shared_ptr<EnvironmentAdapter> GetEnvAdapter();
    };
};

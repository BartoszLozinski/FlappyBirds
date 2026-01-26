#include "CoreLogicAdapter.hpp"

namespace ReinforcementLearning
{
    EnvironmentAdapter::EnvironmentAdapter(const unsigned seed)
    {
        randomGenerator.Seed(seed);
    }

    EnvironmentAdapter::EnvironmentAdapter(const EnvironmentAdapter& other)
    {
        randomGenerator = other.randomGenerator;
    }

    EnvironmentAdapter::EnvironmentAdapter(EnvironmentAdapter&& other)
    {
        randomGenerator = std::move(other.randomGenerator);
    }

    void EnvironmentAdapter::Seed(const unsigned seed)
    {
        randomGenerator.Seed(seed);
    };

    CoreLogicAdapter::CoreLogicAdapter(std::shared_ptr<EnvironmentAdapter> gameEnvAdapterPtr)
        : envAdapter(gameEnvAdapterPtr)
    {
        SetEnvironment(gameEnvAdapterPtr);
    };

    void CoreLogicAdapter::SetEnvironment(std::shared_ptr<EnvironmentAdapter> gameEnvAdapterPtr)
    {
        if (gameEnvAdapterPtr)
        {
            envAdapter = gameEnvAdapterPtr;
            environment = gameEnvAdapterPtr;
        }
    }

    std::shared_ptr<EnvironmentAdapter> CoreLogicAdapter::GetEnvAdapter()
    {
        return envAdapter;
    }

    void CoreLogicAdapter::Seed(const unsigned seed)
    {
        envAdapter->Seed(seed);
    }
};
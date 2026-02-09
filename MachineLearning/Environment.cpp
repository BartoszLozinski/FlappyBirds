#include "Environment.hpp"

namespace ReinforcementLearning
{
    float Environment::ComputeReward(const Gameplay::Event& event) const
    {
        float reward = 0.0;
        const auto& currentState = gameplay.GetState();

        if (!event.birdDied)
            reward += 0.02f + 0.1f * (1.0 - std::abs(currentState.birdY - currentState.pipesGapY) / Game::Config::WINDOW_HEIGHT);
        else //Death reward
            reward -= 1.0f;
        
        if (event.pipePassed) //Pipe passing reward
            reward += 4.0f;

        return reward;
    }
    
    Gameplay::State Environment::Reset()
    {
        gameplay.Reset();
        return gameplay.GetState();
    }

    Gameplay::State Environment::GetState() const
    {
        return gameplay.GetState();
    }

    Environment::Environment()
        : gameplay(CoreLogicAdapter(std::make_shared<EnvironmentAdapter>(42)))
    {}

    void Environment::Seed(unsigned seed)
    {
        gameplay.GetEnvAdapter()->Seed(seed);
    };

    DataTransition Environment::RunStep(ControlOption controlOption)
    {
        Gameplay::Event event = gameplay.RunFrame(controlOption, true);
        Gameplay::State stateAfterAction = gameplay.GetState();
        const bool done = event.birdDied;
        const float reward = ComputeReward(event);

        return { stateAfterAction, reward, done};
    }
}
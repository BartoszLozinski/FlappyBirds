#include "Environment.hpp"

namespace ReinforcementLearning
{
    float Environment::ComputeReward(const Gameplay::State& stateBeforeAction, const Gameplay::State& stateAfterAction, const Gameplay::Event& event) const
    {
        float reward = 0.0;

        //Survival reward
        if (!event.birdDied)
            reward += 0.1f;
        else //Death reward
            reward -= 5.0f;

        //Pipe passing reward
        if (event.pipePassed)
            reward += 1.0f;

        return reward;
    }

    DataTransition Environment::RunStep(ControlOption controlOption)
    {
        Gameplay::State stateBeforeAction = gameplay.GetState();
        Gameplay::Event event = gameplay.RunFrame(controlOption, true);
        Gameplay::State stateAfterAction = gameplay.GetState();
        const bool done = event.birdDied;
        const float reward = ComputeReward(stateBeforeAction, stateAfterAction, event);

        return { stateBeforeAction, event, stateAfterAction, reward, done};
    }
}
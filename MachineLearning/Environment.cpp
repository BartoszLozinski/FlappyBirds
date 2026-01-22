#include "Environment.hpp"

namespace ReinforcementLearning
{
    float Environment::ComputeReward(const Gameplay::Event& event) const
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
    
    Gameplay::State Environment::Reset()
    {
        gameplay.Reset();
        return gameplay.GetState();
    }

    Gameplay::State Environment::GetState() const
    {
        return gameplay.GetState();
    }


    DataTransition Environment::RunStep(ControlOption controlOption)
    {
        Gameplay::Event event = gameplay.RunFrame(controlOption, true);
        Gameplay::State stateAfterAction = gameplay.GetState();
        const bool done = event.birdDied;
        const float reward = ComputeReward(event);

        return { stateAfterAction, reward, done};
    }
}
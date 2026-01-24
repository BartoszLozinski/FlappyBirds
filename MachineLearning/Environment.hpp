#pragma once

#include "../Core/Gameplay/DataProvider.hpp"
#include "../Core/Gameplay/CoreGameplay.hpp"
#include "../Core/Gameplay/State.hpp"

namespace ReinforcementLearning
{
    struct DataTransition
    {
        Gameplay::State stateAfterAction;
        float reward{};
        bool done;
    };

    class Environment
    {
    private:
        Gameplay::CoreLogic gameplay;

    public:
        Environment() = default;
        ~Environment() = default;

        Gameplay::State GetState() const;
        Gameplay::State Reset();
        DataTransition RunStep(ControlOption controlOption);
        [[nodiscard]] float ComputeReward(const Gameplay::Event& event) const;
    };
};
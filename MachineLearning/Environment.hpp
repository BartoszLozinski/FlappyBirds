#pragma once

#include "../Core/Gameplay/DataProvider.hpp"
#include "../Core/Gameplay/State.hpp"
#include "CoreLogicAdapter.hpp"

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
        CoreLogicAdapter gameplay;

    public:
        Environment();
        ~Environment() = default;

        Gameplay::State GetState() const;
        Gameplay::State Reset();
        DataTransition RunStep(ControlOption controlOption);
        void Seed(unsigned seed);
        [[nodiscard]] float ComputeReward(const Gameplay::Event& event) const;
    };
};
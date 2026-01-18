#pragma once

#include "Gameplay/DataProvider.hpp"
#include "Gameplay/CoreGameplay.hpp"

namespace ReinforcementLearning
{
    struct DataTransition
    {
        Gameplay::State stateBeforeAction;
        Gameplay::Event event;
        Gameplay::State stateAfterAction;
        float reward{};
        bool done;
    };

    class Environment
    {
    private:
        Gameplay::CoreLogic& gameplay;

    public:
        Environment(Gameplay::CoreLogic& gameplay_);
        Environment(const Environment& other) = delete;
        Environment(Environment&& other) = delete;
        Environment& operator=(const Environment& other) = delete;
        Environment& operator=(Environment&& other) = delete;
        ~Environment() = default;

        DataTransition RunStep(ControlOption controlOption);
        [[nodiscard]] float ComputeReward(const Gameplay::State& stateBeforeAction, const Gameplay::State& stateAfterAction, const Gameplay::Event& event) const;
    };
};
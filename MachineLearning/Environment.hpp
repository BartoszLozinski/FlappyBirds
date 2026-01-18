#pragma once

#include "../Core/Gameplay/DataProvider.hpp"
#include "../Core/Gameplay/CoreGameplay.hpp"

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
        Gameplay::CoreLogic& gameplay;

    public:
        Environment(Gameplay::CoreLogic& gameplay_);
        Environment(const Environment& other) = delete;
        Environment(Environment&& other) = delete;
        Environment& operator=(const Environment& other) = delete;
        Environment& operator=(Environment&& other) = delete;
        ~Environment() = default;

        Gameplay::State Reset();
        DataTransition RunStep(ControlOption controlOption);
        [[nodiscard]] float ComputeReward(const Gameplay::Event& event) const;
    };
};
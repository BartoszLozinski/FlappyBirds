#pragma once

#include "Gameplay/DataProvider.hpp"
#include "Gameplay/CoreGameplay.hpp"

namespace ReinforcementLearning
{
    struct DataTransition
    {
        Gameplay::State frameState;
        ControlOption controlOption;
        float reward{};
        Gameplay::State nextFrameState;
        bool actionDone;
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

    };
};
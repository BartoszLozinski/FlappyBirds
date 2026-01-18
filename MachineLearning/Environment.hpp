#pragma once

#include "Gameplay/DataProvider.hpp"
#include "Gameplay/CoreGameplay.hpp"

namespace ReinforcementLearning
{
    struct DataTransition
    {
        GameplayState frameState;
        ControlOption controlOption;
        float reward{};
        GameplayState nextFrameState;
        bool actionDone;
    };

    class Environment
    {
    private:
        CoreGameplay& gameplay;

    public:
        Environment(CoreGameplay& gameplay_);
        Environment(const Environment& other) = delete;
        Environment(Environment&& other) = delete;
        Environment& operator=(const Environment& other) = delete;
        Environment& operator=(Environment&& other) = delete;
        ~Environment() = default;

    };
};
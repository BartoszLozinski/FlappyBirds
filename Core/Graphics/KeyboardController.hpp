#pragma once

#include "Utils/ControlOption.hpp"

enum class GameWindowAction
{
    None,
    Stop,
    Restart,
    Quit,
};

namespace Graphics
{
    class KeyboardController
    {
    private:
        bool jumpPressed = false;
        GameWindowAction gameWindowAction = GameWindowAction::None;
        void JumpPressed();
        
    public:

        ControlOption GetControlOption();
        void PullGameWindowAction();
        GameWindowAction GetGameWindowAction() const;
        inline void ResetState() {jumpPressed = false; gameWindowAction = GameWindowAction::None; };
    };
}

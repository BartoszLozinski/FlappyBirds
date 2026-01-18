#pragma once

#include "Utils/ControlOption.hpp"

enum class GameWindowAction
{
    None,
    Start,
    Quit,
};

namespace Graphics
{
    class KeyboardController
    {
    private:
        bool jumpPressed = false;
        GameWindowAction gameWindowAction = GameWindowAction::None;
        ControlOption controlOption = ControlOption::None;
        [[nodiscard]] bool JumpPressed();
        
    public:
        [[nodiscard]] ControlOption GetControlOption() const;
        [[nodiscard]] GameWindowAction GetGameWindowAction() const;
        void PullGameWindowAction();
        void PullControlOption();
        inline void ResetState() {jumpPressed = false; gameWindowAction = GameWindowAction::None; };
    };
}

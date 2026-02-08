#pragma once

#include "Game/IController.hpp"

enum class GameWindowAction
{
    None,
    Start,
    Quit,
};

namespace Graphics
{
    class KeyboardController : public IController
    {
    private:
        bool jumpPressed = false;
        GameWindowAction gameWindowAction = GameWindowAction::None;
        [[nodiscard]] bool JumpPressed();
        
    public:
        [[nodiscard]] ControlOption Decide() const override;
        [[nodiscard]] GameWindowAction GetGameWindowAction() const;
        void PullGameWindowAction();
        void PullControlOption();
        inline void ResetState() {jumpPressed = false; gameWindowAction = GameWindowAction::None; };
    };
}

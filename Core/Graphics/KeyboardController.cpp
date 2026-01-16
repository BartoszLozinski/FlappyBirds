#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

namespace Graphics
{
    void KeyboardController::JumpPressed()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            jumpPressed = true;
    }

    ControlOption KeyboardController::GetControlOption()
    {
        JumpPressed();
        
        if (jumpPressed)
            return ControlOption::Jump;
        
        return ControlOption::None;
    }

    GameWindowAction KeyboardController::GetGameWindowAction() const
    {
        return gameWindowAction;
    }

    void KeyboardController::PullGameWindowAction()
    {
        using enum GameWindowAction;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            gameWindowAction = Quit;
    }
}

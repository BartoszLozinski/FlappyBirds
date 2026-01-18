#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

namespace Graphics
{
    ControlOption KeyboardController::GetControlOption() const
    {
        return controlOption;
    }

    GameWindowAction KeyboardController::GetGameWindowAction() const
    {
        return gameWindowAction;
    }

    bool KeyboardController::JumpPressed()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            jumpPressed = true;

        return jumpPressed;
    }

    void KeyboardController::PullControlOption()
    {
        if (JumpPressed())
            controlOption = ControlOption::Jump;
        else
            controlOption = ControlOption::None;
    }

    void KeyboardController::PullGameWindowAction()
    {
        using enum GameWindowAction;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            gameWindowAction = Quit;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            gameWindowAction = Start;
    }
}

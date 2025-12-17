#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

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
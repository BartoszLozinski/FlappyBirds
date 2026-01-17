#pragma once

#include "Graphics/KeyboardController.hpp"
#include "Gameplay/CoreGameplay.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/Environment.hpp"
#include "Graphics/KeyboardController.hpp"
#include "Graphics/Text.hpp"

class Gameplay : public CoreGameplay
{
private:
    bool gameStarted = false;
    Graphics::Circle renderableBird{ bird };
    Graphics::Environment renderableEnvironment{ *environment };
    sf::RenderWindow window{ sf::VideoMode{ Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT }, "Flappy Birds" };
    Graphics::KeyboardController keyboardController{};
    Graphics::Text pointsText{ window  };

    void DisplayHelpInstructions();
    void UpdateRenderableState();
    void Display();

public:
    void Run();
};

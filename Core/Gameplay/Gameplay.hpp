#pragma once

#include "Graphics/KeyboardController.hpp"
#include "Gameplay/CoreGameplay.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/Pipes.hpp"
#include "Graphics/KeyboardController.hpp"

class Gameplay : public CoreGameplay
{
protected:
    Circle renderableBird{bird};
    Graphics::PipesManager renderablePipes{pipesManager};
    sf::RenderWindow window{sf::VideoMode{GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT}, "Flappy Birds"};
    KeyboardController keyboardController{};

    void UpdateRenderableState();
    void Display();
public:
    void Run();

};

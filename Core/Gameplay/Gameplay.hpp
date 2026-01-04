#pragma once

#include "Graphics/KeyboardController.hpp"
#include "Game/GameConfig.hpp"
#include "Game/Timer.hpp"
#include "Game/Bird.hpp"
#include "Game/Pipes.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/Pipes.hpp"
#include "Graphics/KeyboardController.hpp"

class Gameplay
{
private:
    Bird bird{ Utils::Vector2u{20, 20}, Utils::Vector2f{200, 300} };
    Game::PipesManager pipesManager{};
    Timer frameTimer{1000 / 60};

    Circle renderableBird{bird};
    Graphics::PipesManager renderablePipes{pipesManager};
    sf::RenderWindow window{sf::VideoMode{GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT}, "Flappy Birds"};
    KeyboardController keyboardController{};

    [[maybe_unused]] unsigned points = 0;


    float CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const;
    Game::Pipes& GetClosestPipes() const;
    //bool BirdPassed() const;

public:
    void Run();

};

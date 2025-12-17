#include "Game/GameConfig.hpp"
#include "Game/Timer.hpp"
#include "Game/Bird.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/KeyboardController.hpp"

#include <iostream>
#include <format>
#include <memory>

int main()
{
    auto bird = std::make_shared<Bird>(Utils::Vector2u{10, 20}, Utils::Vector2f{200, 300});

    Circle circle(bird);

    sf::RenderWindow window{sf::VideoMode{GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT}, "Window"};

    KeyboardController keyboardController;

    Timer frameTimer{1000 / 60};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto currentControlOption = keyboardController.GetControlOption();
        bird->Control(currentControlOption);

        //std::cout << std::format("Time elapsed: {}\n", frameTimer.TimeElapsed());

        if (frameTimer.IsExpired())
        {
            //std::cout << std::format("Bird position: ({}, {})\n", bird->GetPosition().x, bird->GetPosition().y);
            window.clear();

            bird->UpdateState();
            circle.UpdatePosition();
            circle.Draw(window);

            window.display();
            frameTimer.Reset();
        }

    }

    return 0;
};

#include <Game/Bird.hpp>

#include <Graphics/Circle.hpp>

#include <iostream>
#include <format>
#include <memory>

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;

int main()
{
    auto bird = std::make_shared<Bird>(Utils::Vector2u{10, 20}, Utils::Vector2f{200, 300});

    Circle circle(bird);

    sf::RenderWindow window{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Window"};

    std::cout << "Init program\n";
    std::cout << std::format("Bird position: ({}, {})\n", bird->GetPosition().x, bird->GetPosition().y); 
    std::cout << std::format("Bird size: ({}, {})\n", bird->GetSize().x, bird->GetSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        circle.Draw(window);
        window.display();

    }

    return 0;
};

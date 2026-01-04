#include "Gameplay.hpp"

void Gameplay::Run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto currentControlOption = keyboardController.GetControlOption();
        bird.Control(currentControlOption);

        if (frameTimer.IsExpired())
        {
            window.clear();

            bird.UpdateState();
            pipesManager.UpdateState();

            renderablePipes.UpdatePosition();
            renderableBird.UpdatePosition();

            renderablePipes.Draw(window);
            renderableBird.Draw(window);

            window.display();
            frameTimer.Reset();
            keyboardController.ResetState();
        }
    }
}
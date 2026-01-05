#include "Gameplay.hpp"

void Gameplay::Display()
{
    window.clear();
    renderablePipes.Draw(window);
    renderableBird.Draw(window);
    window.display();
}

void Gameplay::UpdateRenderableState()
{
    renderableBird.UpdatePosition();
    renderablePipes.UpdatePosition();
}

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

        RunFrame(keyboardController.GetControlOption());

        if (FrameTimeExpired())
        {
            UpdateRenderableState();
            Display();
            keyboardController.ResetState();
        }
    }
}
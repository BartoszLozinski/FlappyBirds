#include "Gameplay.hpp"

void Gameplay::Display()
{
    window.clear();
    renderableEnvironment.Draw(window);
    renderableBird.Draw(window);
    pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
    window.display();
}

void Gameplay::UpdateRenderableState()
{
    renderableBird.UpdatePosition();
    renderableEnvironment.UpdatePosition();
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
        keyboardController.PullGameWindowAction();

        if (FrameTimeExpired())
        {
            UpdateRenderableState();
            Display();
            if (keyboardController.GetGameWindowAction() == GameWindowAction::Quit)
                window.close();

            keyboardController.ResetState();
        }
    }
}
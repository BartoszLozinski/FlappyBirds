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

void Gameplay::DisplayHelpInstructions()
{
    auto helpInstruction = Graphics::Text{ window, { Game::Config::WINDOW_WIDTH * 0.1, Game::Config::WINDOW_HEIGHT * 0.25 }, 40 };

    window.clear();
    renderableEnvironment.Draw(window);
    renderableBird.Draw(window);
    pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
    helpInstruction.DisplayText(std::format("Press {} to start/jump\nPress {} to Quit\n", "SPACE", "Q"));
    window.display();
}

void Gameplay::Run()
{
    while (!gameStarted)
    {
        DisplayHelpInstructions();
        keyboardController.PullGameWindowAction();

        if (keyboardController.GetGameWindowAction() == GameWindowAction::Start)
            gameStarted = true;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frameTimeExpired = frameTimer.IsExpired();
        if (frameTimeExpired)
            frameTimer.Reset();

        RunFrame(keyboardController.GetControlOption(), frameTimeExpired);
        keyboardController.PullGameWindowAction();

        if (frameTimeExpired)
        {
            UpdateRenderableState();
            Display();
            if (keyboardController.GetGameWindowAction() == GameWindowAction::Quit)
                window.close();

            keyboardController.ResetState();
        }
    }
}
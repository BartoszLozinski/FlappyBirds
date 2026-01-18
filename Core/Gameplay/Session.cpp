#include "Session.hpp"

namespace Gameplay
{
    void Session::Display()
    {
        window.clear();
        renderableEnvironment.Draw(window);
        renderableBird.Draw(window);
        pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
        window.display();
    }

    void Session::UpdateRenderableState()
    {
        renderableBird.UpdatePosition();
        renderableEnvironment.UpdatePosition();
    }

    void Session::DisplayHelpInstructions()
    {
        auto helpInstruction = Graphics::Text{ window, { Game::Config::WINDOW_WIDTH * 0.1, Game::Config::WINDOW_HEIGHT * 0.25 }, 40 };

        window.clear();
        renderableEnvironment.Draw(window);
        renderableBird.Draw(window);
        pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
        helpInstruction.DisplayText(std::format("Press {} to start/jump\nPress {} to Quit\n", "SPACE", "Q"));
        window.display();
    }

    void Session::Run()
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

            keyboardController.PullGameWindowAction();
            keyboardController.PullControlOption();

            RunFrame(keyboardController.GetControlOption(), frameTimeExpired);

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
}

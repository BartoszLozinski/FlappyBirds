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

    void Session::HelpInstructions()
    {
        auto instructionKeyboardController = std::make_unique<Graphics::KeyboardController>();
        while (!gameStarted)
        {
            DisplayHelpInstructions();
            instructionKeyboardController->PullGameWindowAction();

            if (instructionKeyboardController->GetGameWindowAction() == GameWindowAction::Start)
                gameStarted = true;
        }
    }

    void Session::GameplayLoop()
    {
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

            auto keyboardController = std::static_pointer_cast<Graphics::KeyboardController>(controller);
            keyboardController->PullGameWindowAction();
            keyboardController->PullControlOption();

            RunFrame(controller->Decide(), frameTimeExpired);

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
                if (keyboardController->GetGameWindowAction() == GameWindowAction::Quit)
                    window.close();

                keyboardController->ResetState();
            }
        }
    }

    void Session::Run()
    {
        HelpInstructions();
        GameplayLoop();
    }

    void Session::UpdateRenderableState()
    {
        renderableBird.UpdatePosition();
        renderableEnvironment.UpdatePosition();
    }
}

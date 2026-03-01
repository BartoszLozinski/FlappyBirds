#include "Session.hpp"

namespace Gameplay
{
    Session::Session(std::shared_ptr<IController> controller_)
        : BaseSession( window, controller_)
    {}

    void Session::Display()
    {
        Draw(target);
        window.display();
    }

    void Session::DisplayHelpInstructions()
    {
        DrawHelpInstructions();
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

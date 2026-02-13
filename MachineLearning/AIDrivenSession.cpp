#include "AIDrivenSession.hpp"

namespace Gameplay
{
    AIDrivenSession::AIDrivenSession()
    {
        controller = mlController;
    }

    void AIDrivenSession::GameplayLoop()
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

            mlController->UpdateStatus(GetState());
            
            RunFrame(mlController->Decide(), frameTimeExpired);

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
            }
        }
    }

    void AIDrivenSession::Run()
    {
        HelpInstructions();
        GameplayLoop();
    }
}

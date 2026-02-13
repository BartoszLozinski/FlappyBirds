#include "AIDrivenSession.hpp"

namespace Gameplay
{
    AIDrivenSession::AIDrivenSession()
        : Session(std::make_shared<ReinforcementLearning::MLController>("../TrainedModel/genetic_algorithm_flappy.json"))
    {}

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

            auto mlController = static_pointer_cast<ReinforcementLearning::MLController>(controller);
            mlController->UpdateStatus(GetState());
            
            RunFrame(controller->Decide(), frameTimeExpired);

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
            }
        }
    }

    void AIDrivenSession::Run()
    {
        window.setTitle("AI Driven FlappyBirds");
        HelpInstructions();
        GameplayLoop();
    }
}

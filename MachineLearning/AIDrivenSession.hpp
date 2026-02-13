#pragma once
#include "Gameplay/Session.hpp"
#include "MLController.hpp"

namespace Gameplay
{
    class AIDrivenSession : public Session
    {
    protected:
        std::shared_ptr<ReinforcementLearning::MLController> mlController = std::make_shared<ReinforcementLearning::MLController>("../TrainedModel/genetic_algorithm_flappy.json");
        void GameplayLoop() override;

    public:
        AIDrivenSession();
        void Run() override;
    };
}
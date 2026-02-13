#pragma once
#include "Gameplay/Session.hpp"
#include "MLController.hpp"

namespace Gameplay
{
    class AIDrivenSession : public Session
    {
    protected:
        void GameplayLoop() override;

    public:
        AIDrivenSession();
        void Run() override;
    };
}
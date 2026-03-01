#pragma once

#include "Gameplay/CoreGameplay.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/Environment.hpp"
#include "Game/IController.hpp"
#include "Graphics/Text.hpp"

namespace Gameplay
{
    class BaseSession : public CoreLogic
    {
    protected:
        Timer frameTimer{1000 / 60};
        bool frameTimeExpired = false;

        bool gameStarted = false;
        Graphics::Circle renderableBird{ bird };
        Graphics::Environment renderableEnvironment{ *environment };
        sf::RenderTarget& target;
        std::shared_ptr<IController> controller = nullptr;
        Graphics::Text pointsText{ target };

        void Draw(sf::RenderTarget& target);
        void DrawHelpInstructions();
        void UpdateRenderableState();
        virtual void GameplayLoop() = 0;

        BaseSession(sf::RenderTarget& target, std::shared_ptr<IController> controller_);

    public:
        BaseSession() = delete;
        virtual void Run() = 0;
        virtual ~BaseSession() = default;
    };
}
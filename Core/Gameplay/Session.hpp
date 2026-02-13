#pragma once

#include "Graphics/KeyboardController.hpp"
#include "Gameplay/CoreGameplay.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/Environment.hpp"
#include "Graphics/KeyboardController.hpp"
#include "Graphics/Text.hpp"

namespace Gameplay
{
    class Session : public CoreLogic
    {
    protected:
        Timer frameTimer{1000 / 60};
        bool frameTimeExpired = false;

        bool gameStarted = false;
        Graphics::Circle renderableBird{ bird };
        Graphics::Environment renderableEnvironment{ *environment };
        sf::RenderWindow window{ sf::VideoMode{ Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT }, "Flappy Birds" };
        std::shared_ptr<IController> controller = std::make_shared<Graphics::KeyboardController>();
        Graphics::Text pointsText{ window  };

        void Display();
        void DisplayHelpInstructions();
        void UpdateRenderableState();
        void HelpInstructions();
        virtual void GameplayLoop();

        Session(std::shared_ptr<IController> controller_);

    public:
        Session() = default;
        virtual void Run();
    };
}
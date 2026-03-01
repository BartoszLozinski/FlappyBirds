#pragma once

#include "Gameplay/BaseSession.hpp"
#include "Graphics/KeyboardController.hpp"


namespace Gameplay
{
    class Session : public BaseSession
    {
    protected:
        sf::RenderWindow window{ sf::VideoMode{ Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT }, "Flappy Birds" };

        void Display();
        void DisplayHelpInstructions();
        void UpdateRenderableState();
        void HelpInstructions();
        void GameplayLoop() override;

    public:
        Session(std::shared_ptr<IController> controller_ = std::make_shared<Graphics::KeyboardController>());
        void Run() override;
        ~Session() = default;
    };
}
#include "BaseSession.hpp"

namespace Gameplay
{
    BaseSession::BaseSession(sf::RenderTarget& target, std::shared_ptr<IController> controller_)
        : target(target)
        , controller(controller_)
    {}

    void BaseSession::Draw(sf::RenderTarget& target)
    {
        target.clear();
        renderableEnvironment.Draw(target);
        renderableBird.Draw(target);
        pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
    }

    void BaseSession::DrawHelpInstructions()
    {
        auto helpInstruction = Graphics::Text{ target, { Game::Config::WINDOW_WIDTH * 0.1, Game::Config::WINDOW_HEIGHT * 0.25 }, 40 };

        target.clear();
        renderableEnvironment.Draw(target);
        renderableBird.Draw(target);
        pointsText.DisplayText(std::format("Points: {}", bird.GetPoints()));
        helpInstruction.DisplayText(std::format("Press {} to start/jump\nPress {} to Quit\n", "SPACE", "Q"));
    }

    void BaseSession::UpdateRenderableState()
    {
        renderableBird.UpdatePosition();
        renderableEnvironment.UpdatePosition();
    }
}

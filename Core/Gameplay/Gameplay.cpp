#include "Gameplay.hpp"


float Gameplay::CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const
{
    const float pipesXPosition = pipes->GetPipesSegment().begin()->GetPosition().x;
    return pipesXPosition - bird.GetPosition().x;
}

Game::Pipes& Gameplay::GetClosestPipes() const
{
    const auto& pipes = pipesManager.GetPipes();
    auto closestPipes = pipes.end();
    auto currentPipe = pipes.begin();

    while(currentPipe != pipes.end())
    {
        const float xDistance = CalculateXDsitance(*currentPipe);

        if (xDistance >= 0 &&
            (closestPipes == pipes.end() || xDistance < CalculateXDsitance(*closestPipes)))
        {
            closestPipes = currentPipe;
        }

        currentPipe++;
    }

    return *closestPipes->get();
}

void Gameplay::Run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        const auto currentControlOption = keyboardController.GetControlOption();
        bird.Control(currentControlOption);

        if (frameTimer.IsExpired())
        {
            window.clear();

            bird.UpdateState();
            pipesManager.UpdateState();

            renderablePipes.UpdatePosition();
            renderableBird.UpdatePosition();

            renderablePipes.Draw(window);
            renderableBird.Draw(window);

            window.display();
            frameTimer.Reset();
            keyboardController.ResetState();
        }
    }
}
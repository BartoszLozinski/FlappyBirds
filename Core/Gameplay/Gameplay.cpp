#include "Gameplay.hpp"

#include <assert.h>


float Gameplay::CalculateXDsitance(const std::unique_ptr<Game::Pipes>& pipes) const
{
    const float pipesXPosition = pipes->GetPipesSegment().begin()->GetPosition().x;
    return pipesXPosition - bird.GetPosition().x;
}

float Gameplay::CalculateXDsitance(const Game::Pipes& pipes) const
{
    const float pipesXPosition = pipes.GetPipesSegment().begin()->GetPosition().x;
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

    assert(closestPipes != pipes.end());
    return *closestPipes->get();
}

unsigned Gameplay::GetPoints() const
{
    return points;
}

void Gameplay::UpdateState()
{
    bird.UpdateState();
    pipesManager.UpdateState();
    renderablePipes.UpdatePosition();
    renderableBird.UpdatePosition();
}

void Gameplay::UpdatePoints(const Utils::Vector2f& closestPipesPositionBeforeUpdateState, const Game::Pipes& closestPipes)
{
    const auto birdPosition = bird.GetPosition();
    if (closestPipesPositionBeforeUpdateState.x >= birdPosition.x && CalculateXDsitance(closestPipes) <= 0.0f)
        points++;
}

void Gameplay::Display()
{
    window.clear();
    renderablePipes.Draw(window);
    renderableBird.Draw(window);
    window.display();
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
            const auto& closestPipes = GetClosestPipes();
            const auto closestPipesPositionBeforeUpdateState = closestPipes.GetPipesSegment()[0].GetPosition();

            UpdateState();
            UpdatePoints(closestPipesPositionBeforeUpdateState, closestPipes);

            Display();

            frameTimer.Reset();
            keyboardController.ResetState();
        }
    }
}
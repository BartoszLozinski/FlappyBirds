#include "DataProvider.hpp"

#include <format>

namespace Gameplay
{
    void DataProvider::SetState(const Game::Bird& bird, const Game::Pipes& pipes)
    {
        gameplayState.birdX = bird.GetPosition().x;
        gameplayState.birdY = bird.GetPosition().y;
        gameplayState.birdSize = bird.GetSize().x;
        gameplayState.birdVy = bird.GetVelocity().y;

        const auto& pipesSegment = pipes.GetPipesSegment();

        gameplayState.nextPipeX = pipesSegment.front().GetPosition().x;
        gameplayState.topPipeY = pipesSegment[0].GetPosition().y;
        gameplayState.bottomPipeY = pipesSegment[1].GetPosition().y;
        gameplayState.pipeSizeX = pipesSegment[0].GetSize().x;
        gameplayState.pipeSizeY = pipesSegment[0].GetSize().y;
        gameplayState.birdAbleToJump = bird.IsAbleToJump();
        gameplayState.framesSinceLastJump = bird.GetFramesSinceLastJump();
        gameplayState.birdAlive = bird.IsAlive();
    }

    std::string DataProvider::GetRow() const
    {
        static constexpr unsigned  TRUE = 1;
        static constexpr unsigned FALSE = 0;

        return std::format("{:.0f},{:.0f},{},{:.0f},{:.0f},{:.0f},{:.0f},{},{},{},{}",
            gameplayState.birdX,
            gameplayState.birdY,
            gameplayState.birdSize,
            gameplayState.birdVy,
            gameplayState.nextPipeX,
            gameplayState.topPipeY,
            gameplayState.bottomPipeY,
            gameplayState.pipeSizeX,
            gameplayState.pipeSizeY,
            gameplayState.birdAbleToJump ? TRUE : FALSE,
            gameplayState.framesSinceLastJump,
            gameplayState.birdAlive ? TRUE : FALSE
            );
    }

    State DataProvider::GetGameplayState() const
    {
        return gameplayState;
    }

    std::string DataProvider::GetHeader() const
    {
        return "BirdX,BirdY,BirdSize,BirdVy,NextPipeX,TopPipeY,BottomPipeY,PipeSizeX,PipesSizeY,BirdAbleToJump,FramesSinceLastJump,BirdAlive";
    }
}

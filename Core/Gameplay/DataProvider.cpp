#include "DataProvider.hpp"

#include <format>

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
    gameplayState.pipesSizeY = pipesSegment[0].GetSize().y;
    gameplayState.birdAbleToJump = bird.IsAbleToJump();
    gameplayState.framesSinceLastJump = bird.GetFramesSinceLastJump();
    gameplayState.birdAlive = bird.IsAlive();
    //gameplayState.points = bird.GetPoints();
    //gameplayState.action = static_cast<unsigned>(controlOption);
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
        gameplayState.pipesSizeY,
        gameplayState.birdAbleToJump ? TRUE : FALSE,
        gameplayState.framesSinceLastJump,
        gameplayState.birdAlive ? TRUE : FALSE
        //gameplayState.points,
        //gameplayState.action
        );
}

GameplayState DataProvider::GetGameplayState() const
{
    return gameplayState;
}

std::string DataProvider::GetHeader() const
{
    return "BirdX,BirdY,BirdSize,BirdVy,NextPipeX,TopPipeY,BottomPipeY,PipeSizeX,PipesSizeY,BirdAbleToJump,FramesSinceLastJump,BirdAlive";
}

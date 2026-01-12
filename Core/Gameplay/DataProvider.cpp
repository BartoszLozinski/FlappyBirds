#include "DataProvider.hpp"

#include <format>

void DataProvider::SetState(uint64_t frameIdx_, const Game::Bird& bird, const Game::Pipes& pipes, const ControlOption controlOption)
{
    frameIdx = frameIdx_;
    birdX = bird.GetPosition().x;
    birdY = bird.GetPosition().y;
    birdSize = bird.GetSize().x;
    birdVy = bird.GetVelocity().y;

    const auto& pipesSegment = pipes.GetPipesSegment();

    nextPipeX = pipesSegment.front().GetPosition().x;
    topPipeY = pipesSegment[0].GetPosition().y;
    bottomPipeY = pipesSegment[1].GetPosition().y;
    pipeSizeX = pipesSegment[0].GetSize().x;
    pipesSizeY = pipesSegment[0].GetSize().y;
    birdAbleToJump = bird.IsAbleToJump();
    framesSinceLastJump = bird.GetFramesSinceLastJump();
    birdAlive = bird.IsAlive();
    points = bird.GetPoints();
    action = static_cast<unsigned>(controlOption);
}

std::string DataProvider::GetRow() const
{
    static constexpr unsigned  TRUE = 1;
    static constexpr unsigned FALSE = 0;

    return std::format("{},{:.0f},{:.0f},{},{:.0f},{:.0f},{:.0f},{},{},{},{},{},{},{}",
        frameIdx,
        birdX,
        birdY,
        birdSize,
        birdVy,
        nextPipeX,
        topPipeY,
        bottomPipeY,
        pipeSizeX,
        pipesSizeY,
        birdAbleToJump ? TRUE : FALSE,
        framesSinceLastJump,
        birdAlive ? TRUE : FALSE,
        points,
        action);
}

std::string DataProvider::GetHeader() const
{
    return "FrameIdx,BirdX,BirdY,BirdSize,BirdVy,NextPipeX,TopPipeY,BottomPipeY,PipeSizeX,PipesSizeY,BirdAbleToJump,FramesSinceLastJump,BirdAlive,Points,Action";
}

#include "CVSession.hpp"
#include "../MachineLearning/MLController.hpp"

#include <opencv2/imgproc.hpp>

//to be removed after testing
#include "Gameplay/CoreGameplay.hpp"
#include <iostream>
#include <format>

namespace Gameplay
{
    CVSession::CVSession(): AIDrivenSession(){}

    cv::Mat CVSession::CaptureFrame() const
    {
        sf::Texture texture;
        texture.create(Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT);
        texture.update(window);

        sf::Image image = texture.copyToImage();
        const sf::Uint8* pixels = image.getPixelsPtr();

        cv::Mat mat( image.getSize().y
                   , image.getSize().x
                   , CV_8UC4
                   , const_cast<sf::Uint8*>(pixels));

        cv::Mat bgr;
        cv::cvtColor(mat, bgr, cv::COLOR_RGBA2BGR);
        return bgr.clone();
    }

    void CVSession::GameplayLoop()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            frameTimeExpired = frameTimer.IsExpired();
            if (frameTimeExpired)
                frameTimer.Reset();

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
                observer.SetFrame(CaptureFrame());
                observer.ShowFrame();
                auto mlController = std::make_shared<ReinforcementLearning::MLController>("../TrainedModel/genetic_algorithm_flappy.json");
                mlController->UpdateStatus(GetState());
            
                RunFrame(controller->Decide(), frameTimeExpired);
            }
        }
    }

    std::pair<std::size_t, std::size_t> CVSession::GetClosestPipesIndexes(const std::vector<cv::Rect>& pipes) const
    {
        std::size_t first = 0;
        std::size_t second = 1;

        if (pipes[second].x < pipes[first].x)
            std::swap(first, second);

        for (std::size_t i = 2; i < pipes.size(); i++)
        {
            if (pipes[i].x < pipes[first].x)
            {   second = first;
                first = i;
            }
            else if (pipes[i].x < pipes[second].x)
            {
                second = i;
            }
        }

        return { first, second };
    }

    State CVSession::GetState() const
    {
        State state{};

        const auto birdCVData = observer.DetectCircle();
        state.birdX = birdCVData[0];
        state.birdY = birdCVData[1];
        state.birdSize = birdCVData[2] * 2; // OpenCV provides radius, while game uses diameter (bounding box)
        state.birdVy = bird.GetVelocity().y; //Can update to calculate position derivative in future (pixels)

        const auto pipes = observer.DetectRectangles();
        const auto closestPipesIndexes = GetClosestPipesIndexes(pipes);

        const auto topPipeIndex = pipes[closestPipesIndexes.first].y < pipes[closestPipesIndexes.second].y ? closestPipesIndexes.first : closestPipesIndexes.second;
        const auto bottomPipeIndex = topPipeIndex == closestPipesIndexes.first ? closestPipesIndexes.second : closestPipesIndexes.first;
        
        state.nextPipeX = pipes[closestPipesIndexes.first].x;
        state.gapTopVertexY = pipes[topPipeIndex].y + pipes[topPipeIndex].height;
        state.gapBottomVertexY = pipes[bottomPipeIndex].y;
        //testing
        //model needs to be changed to detect pipes vertexes nearest to the gap
        //instead of finidng center of the rectangle (even if its out of the window)

        //state.pipesGapY = (Game::Config::WINDOW_HEIGHT - pipes[bottomPipeIndex].y + pipes[topPipeIndex].y + pipes[topPipeIndex].height) / 2;
        state.birdAbleToJump = bird.IsAbleToJump();
        state.framesSinceLastJump = bird.GetFramesSinceLastJump();
        state.birdAlive = bird.IsAlive();

        std::cout << "State passed to observer:\n";
        std::cout << std::format("BirdY: {}, BirdVy: {}, NextPipeX: {}, GapTopY: {}, GapBottomY: {}, AbleToJump: {}, FramesSinceLastJump: {}, BirdAlive: {}\n",
            state.birdY, state.birdVy, state.nextPipeX, state.gapTopVertexY, state.gapBottomVertexY, state.birdAbleToJump, state.framesSinceLastJump, state.birdAlive);

        return state;
    }

    void CVSession::Run()
    {
        window.setTitle("Base AI driven session");
        GameplayLoop();
    }
}

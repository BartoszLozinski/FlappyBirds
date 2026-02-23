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

            observer.SetFrame(CaptureFrame());
            auto mlController = static_pointer_cast<ReinforcementLearning::MLController>(controller);
            mlController->UpdateStatus(GetState());
            
            RunFrame(mlController->Decide(), frameTimeExpired);

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
                observer.SetFrame(CaptureFrame());
                observer.ShowFrame();
            }
        }
    }

    std::pair<std::size_t, std::size_t> CVSession::GetClosestPipesIndexes(const float birdX, const std::vector<cv::Rect>& pipes) const
    {
        const float tolerance = 5.f; // pixels
        float minDistance = std::numeric_limits<float>::max();
        float targetX = -1.f;

        // STEP 1: Find closest pipe column in front of bird
        for (const auto& rect : pipes)
        {
            float centerX = rect.x + rect.width / 2.f;

            if (centerX > birdX) // only in front
            {
                float distance = centerX - birdX;

                if (distance < minDistance)
                {
                    minDistance = distance;
                    targetX = centerX;
                }
            }
        }

        // STEP 2: Collect two rectangles with similar X
        std::size_t first = 0;
        std::size_t second = 0;
        bool foundFirst = false;

        for (std::size_t i = 0; i < pipes.size(); ++i)
        {
            float centerX = pipes[i].x + pipes[i].width / 2.f;

            if (std::abs(centerX - targetX) < tolerance)
            {
                if (!foundFirst)
                {
                    first = i;
                    foundFirst = true;
                }
                else
                {
                    second = i;
                    break;
                }
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
        const auto closestPipesIndexes = GetClosestPipesIndexes(state.birdX, pipes);

        const auto topPipeIndex = pipes[closestPipesIndexes.first].y < pipes[closestPipesIndexes.second].y ? closestPipesIndexes.first : closestPipesIndexes.second;
        const auto bottomPipeIndex = topPipeIndex == closestPipesIndexes.first ? closestPipesIndexes.second : closestPipesIndexes.first;
        
        state.nextPipeX = pipes[closestPipesIndexes.first].x + pipes[closestPipesIndexes.first].width / 2.f; // center of the pipe column
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

        std::cout << "Gameplay state (old way):\n";
        auto gameplayState = Session::GetState();
        std::cout << std::format("GameBirdY: {}, GameBirdVy: {}, GameNextPipeX: {}, GameGapTopY: {}, GameGapBottomY: {}, GameAbleToJump: {}, FameFramesSinceLastJump: {}, BirdAlive: {}\n",
            gameplayState.birdY, gameplayState.birdVy, gameplayState.nextPipeX, gameplayState.gapTopVertexY, gameplayState.gapBottomVertexY, gameplayState.birdAbleToJump, gameplayState.framesSinceLastJump, gameplayState.birdAlive);


        return state;
    }

    void CVSession::Run()
    {
        window.setTitle("Base AI driven session");
        UpdateRenderableState();
        Display();
        observer.SetFrame(CaptureFrame());
        observer.ShowFrame();
        GameplayLoop();
    }
}

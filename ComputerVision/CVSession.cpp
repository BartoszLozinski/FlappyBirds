#include "CVSession.hpp"
#include "../MachineLearning/MLController.hpp"

#include <opencv2/imgproc.hpp>

#include <iostream>
#include <format>

namespace Gameplay
{
    CVSession::CVSession()
        : BaseSession(texture , std::make_shared<ReinforcementLearning::MLController>("../TrainedModel/genetic_algorithm_flappy.json"))
    {
        texture.create(Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT);
    }

    cv::Mat CVSession::CaptureFrame() const
    {
        sf::Image image = texture.getTexture().copyToImage();
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
        bool running = true;
        auto mlController = static_pointer_cast<ReinforcementLearning::MLController>(controller);

        //only for performance measurement
        Timer singleFrameTimer{ std::numeric_limits<int64_t>::max() };
        singleFrameTimer.Reset();
        unsigned framesCounter = 0;

        while (running)
        {
            frameTimeExpired = frameTimer.IsExpired();
            if (frameTimeExpired)
                frameTimer.Reset();

            if (frameChanged)
            {
                observer.SetFrame(CaptureFrame());
                mlController->UpdateStatus(GetState());
                
                frameChanged = false;
            }

            if (frameTimeExpired)
            {
                RunFrame(mlController->Decide());
                UpdateRenderableState();
                texture.clear();
                Draw(texture);
                texture.display();
                observer.ShowFrame();
                frameChanged = true;

                framesCounter++;
                
                if (framesCounter >= 10)
                {
                    std::cout << std::format("Frame time elapsed (averaged for 10 frames): {} ms\n", singleFrameTimer.TimeElapsed() / framesCounter);
                    singleFrameTimer.Reset();
                    framesCounter = 0;
                }
            }

            if (!bird.IsAlive())   
                running = false;
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
        state.birdAbleToJump = bird.IsAbleToJump();
        state.framesSinceLastJump = bird.GetFramesSinceLastJump();
        state.birdAlive = bird.IsAlive();

        return state;
    }

    void CVSession::Run()
    {
        texture.create(Game::Config::WINDOW_WIDTH, Game::Config::WINDOW_HEIGHT);
        UpdateRenderableState();
        texture.clear();
        Draw(texture);
        texture.display();
        observer.SetFrame(CaptureFrame());
        observer.ShowFrame();
        GameplayLoop();
    }
}

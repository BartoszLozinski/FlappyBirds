#pragma once
#include "../MachineLearning/AIDrivenSession.hpp"
#include "Observer.hpp"
#include <opencv2/core.hpp>

#include <utility>

namespace Gameplay
{
    // This session will be driven by same neural network as AIDrivenSession,
    // but environment data (pipes and birds position) will be provided by CV
    class CVSession : public AIDrivenSession
    {
    protected:
        void GameplayLoop() override;
        cv::Mat CaptureFrame() const;
        ComputerVision::Observer observer;
        std::pair<std::size_t, std::size_t> GetClosestPipesIndexes(const std::vector<cv::Rect>& pipes) const;

    public:
        CVSession();
        State GetState() const override;
        void Run() override;
    };
}
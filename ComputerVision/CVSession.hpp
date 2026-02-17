#pragma once
#include "../MachineLearning/AIDrivenSession.hpp"
#include "Observer.hpp"
#include <opencv2/core.hpp>

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

    public:
        CVSession();
        void Run() override;
    };
}
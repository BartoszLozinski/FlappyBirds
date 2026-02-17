#pragma once

#include <opencv2/core.hpp>

namespace ComputerVision
{
    class Observer
    {
    private:
        cv::Mat frame;
        cv::Mat grayFrame;
        cv::Mat binaryFrame;

        void UpdateBinaryFrame();
        void UpdateGrayFrame();
        void DisplayBirdBoundaries(const cv::Vec3f& circle);
        
    public:
        cv::Vec3f DetectCircle();
        std::vector<cv::Rect> DetectRectangles();
        void SetFrame(cv::Mat frame_);
        void ShowFrame();
    };

};
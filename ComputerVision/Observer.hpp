#pragma once

#include <opencv2/core.hpp>
#include "Utils/Utils.hpp"

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
        void DisplayPipesBoundaries(const std::vector<cv::Rect>& rectangles);

    public:
        cv::Vec3f DetectCircle() const;
        std::vector<cv::Rect> DetectRectangles() const;
        void SetFrame(cv::Mat frame_);
        void ShowFrame();

        Utils::Vector2f GetObjectPosition(const cv::Vec3f& object) const;
        Utils::Vector2f GetObjectPosition(const cv::Rect& object) const;
        Utils::Vector2f GetRectangleSize(const cv::Rect& object) const;
    };

};
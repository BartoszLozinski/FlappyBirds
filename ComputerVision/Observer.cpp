#include "Observer.hpp"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace ComputerVision
{
    void Observer::UpdateBinaryFrame()
    {
        cv::threshold(grayFrame, binaryFrame, 100, 255, cv::THRESH_BINARY_INV);
        cv::bitwise_not(binaryFrame, binaryFrame);
    }

    void Observer::UpdateGrayFrame()
    {
        if (frame.empty())
            return;

        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(grayFrame, grayFrame, cv::Size(9, 9), 2);
    }

    cv::Vec3f Observer::DetectCircle() const
    {
        if (grayFrame.empty())
            return {};

        std::vector<cv::Vec3f> circle;

        static constexpr double inverseRatio = 1;
        static constexpr double minDist = 50;
        static constexpr double edgeDetectionThreshold = 100;
        static constexpr double centerDetectionThreshold = 30;
        static constexpr int minRadius = 5;
        static constexpr int maxRadius = 30;

        cv::HoughCircles( grayFrame
                        , circle
                        , cv::HOUGH_GRADIENT
                        , inverseRatio
                        , minDist
                        , edgeDetectionThreshold
                        , centerDetectionThreshold
                        , minRadius
                        , maxRadius);
                        
        if (!circle.empty())
            return circle[0];
        
        return {};
    };

    std::vector<cv::Rect> Observer::DetectRectangles() const
    {
        std::vector<cv::Rect> rectangles;

        if (binaryFrame.empty())
            return rectangles;

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(binaryFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours)
        {
            cv::Rect rectangle = cv::boundingRect(contour);
            if (rectangle.area() > 2000)
                rectangles.push_back(rectangle);
        }

        return rectangles;
    }

    void Observer::DisplayBirdBoundaries(const cv::Vec3f& circle)
    {
        cv::Point center{ cvRound(circle[0]), cvRound(circle[1]) };
        const int radius{ cvRound(circle[2]) };

        //circle outline (blue)
        cv::circle(frame, center, radius, cv::Scalar{255, 0, 0}, 3);
        cv::circle(frame, center, 3, cv::Scalar{255, 0, 0}, -1);
    }

    void Observer::DisplayPipesBoundaries(const std::vector<cv::Rect>& rectangles)
    {
        static constexpr int lineThickness = 3;

        for (const auto& rectangle : rectangles)
        {
            cv::rectangle(frame, rectangle, cv::Scalar{0, 0, 255}, lineThickness);
            cv::circle(frame, cv::Point{rectangle.x, rectangle.y}, 2, cv::Scalar{0, 0, 255}, -1);//center
        }
    }

    Utils::Vector2f Observer::GetObjectPosition(const cv::Vec3f& object) const
    {
        return { object[0], object[1] };
    }
    
    Utils::Vector2f Observer::GetObjectPosition(const cv::Rect& object) const
    {
        return { static_cast<float>(object.x), static_cast<float>(object.y) };
    }

    Utils::Vector2f Observer::GetRectangleSize(const cv::Rect& object) const
    {
        return { static_cast<float>(object.width), static_cast<float>(object.height) };
    }

    void Observer::SetFrame(cv::Mat frame_)
    {
        frame = frame_;
    }

    void Observer::ShowFrame()
    {
        UpdateGrayFrame();
        UpdateBinaryFrame();
        DisplayBirdBoundaries(DetectCircle());
        DisplayPipesBoundaries(DetectRectangles());

        cv::imshow("CV-FlappyBirds Session", frame);
        cv::waitKey(1);
    }
};

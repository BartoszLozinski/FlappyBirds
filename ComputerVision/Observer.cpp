#include "Observer.hpp"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace ComputerVision
{
    void Observer::UpdateGrayImage()
    {
        if (frame.empty())
            return;

        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(grayFrame, grayFrame, cv::Size(9, 9), 2);
    }

    cv::Vec3f Observer::DetectCircle()
    {
        if (grayFrame.empty())
            return {};

        cv::Vec3f circle;

        static constexpr double inverseRatio = 1;
        static constexpr double minDist = 50;
        static constexpr double edgeDetectionThreshold = 100;
        static constexpr double centerDetectionThreshold = 30;
        static constexpr double minRadius = 5;
        static constexpr double maxRadius = 30;

        cv::HoughCircles( grayFrame
                        , circle
                        , cv::HOUGH_GRADIENT
                        , inverseRatio
                        , minDist
                        , edgeDetectionThreshold
                        , centerDetectionThreshold
                        , minRadius
                        , maxRadius);
                        
        return circle;
    };

    std::vector<cv::Rect> Observer::DetectRectangles()
    {
        std::vector<cv::Rect> rectangles;
        cv::threshold(grayFrame, binaryFrame, 100, 255, cv::THRESH_BINARY_INV);

        if (binaryFrame.empty())
            return rectangles;

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(binaryFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours)
        {
            std::vector<cv::Point> approxRectangle;
            cv::approxPolyDP( contour
                            , approxRectangle
                            , 0.02 * cv::arcLength(contour, true)
                            , true);

            if (approxRectangle.size() == 4 && cv::isContourConvex(approxRectangle))
            {
                cv::Rect rectangle = cv::boundingRect(approxRectangle);

                if (rectangle.area() > 100)
                    rectangles.push_back(rectangle);
            }
        }

        return rectangles;
    }

    void Observer::SetFrame(cv::Mat frame_)
    {
        frame = frame_;
    }

    void Observer::ShowFrame()
    {
        cv::imshow("CV-FlappyBirds Session", frame);
        cv::waitKey(1);
    }
};

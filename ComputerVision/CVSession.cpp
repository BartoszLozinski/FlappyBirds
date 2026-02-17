#include "CVSession.hpp"
#include "../MachineLearning/MLController.hpp"

#include <opencv2/imgproc.hpp>

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

            auto mlController = static_pointer_cast<ReinforcementLearning::MLController>(controller);
            mlController->UpdateStatus(GetState());
            
            RunFrame(controller->Decide(), frameTimeExpired);

            if (frameTimeExpired)
            {
                UpdateRenderableState();
                Display();
                observer.SetFrame(CaptureFrame());
                observer.ShowFrame();
            }
        }
    }

    void CVSession::Run()
    {
        window.setTitle("Base AI driven session");
        GameplayLoop();
    }
}

#include "UI.hpp"

UI::UI(int& argc, char** argv)
    : app(std::make_unique<QApplication>(argc, argv))
    , mainWindow(std::make_unique<QWidget>())
{
    mainWindow->setWindowTitle("Flappy Birds");
    mainWindow->resize(200, 50);

    layout->addWidget(startButton.GetButton().get());
    layout->addWidget(startAIGameButton.GetButton().get());
};

void UI::showMainWindow()
{
    mainWindow->show();
}

int UI::RunExec()
{
    return app->exec();
}


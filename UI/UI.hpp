#pragma once

#include <QApplication>
#include <QLabel>
#include <QPointer>
#include <QString>
#include <QWidget>
#include <QHBoxLayout>


#include <memory>
#include "Button.hpp"

//#include "Core/Gameplay/Gameplay.hpp"

class UI
{
private:
    std::unique_ptr<QApplication> app = nullptr;
    std::unique_ptr<QWidget> mainWindow = nullptr;

    std::unique_ptr<QHBoxLayout> layout = std::make_unique<QHBoxLayout>(mainWindow.get());
    Button startButton{ "Start" };
    Button restartButton{ "Restart" };

    //Gameplay gameplay{};

public:
    UI(int& argc, char** argv);
    ~UI() = default;

    void showMainWindow();
    int RunExec();
};

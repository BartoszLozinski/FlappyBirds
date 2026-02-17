#pragma once

#include <QApplication>
#include <QLabel>
#include <QPointer>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>

#include <memory>
#include "StartButton.hpp"
#include "StartAIGameButton.hpp"
#include "StartCVSessionButton.hpp"
class UI
{
private:
    std::unique_ptr<QApplication> app = nullptr;
    std::unique_ptr<QWidget> mainWindow = nullptr;

    std::unique_ptr<QVBoxLayout> layout = std::make_unique<QVBoxLayout>(mainWindow.get());
    StartButton startButton{ "Start" };
    StartAIGameButton startAIGameButton{ "StartAIDrivenSession" };
    StartCVSessionButton startCVSessionButton{ "StartCVSession" };

public:
    UI(int& argc, char** argv);
    ~UI() = default;

    void showMainWindow();
    int RunExec();
};

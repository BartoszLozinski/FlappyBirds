#pragma once

#include <QApplication>
#include <QLabel>
#include <QPointer>
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <memory>

class UI
{
private:
    std::unique_ptr<QApplication> app = nullptr;
    std::unique_ptr<QWidget> mainWindow = nullptr;

    std::unique_ptr<QHBoxLayout> layout = std::make_unique<QHBoxLayout>(mainWindow.get());
    std::unique_ptr<QPushButton> startButton = std::make_unique<QPushButton>("Start");
    std::unique_ptr<QPushButton> restartButton = std::make_unique<QPushButton>("Restart");

public:
    UI(int& argc, char** argv);
    ~UI() = default;

    void showMainWindow();
    int RunExec();
};

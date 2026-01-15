#pragma once

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QString>
#include <QWidget>

#include <memory>

class UI
{
private:
    std::unique_ptr<QApplication> app = nullptr;
    std::unique_ptr<QWidget> mainWindow = nullptr;

public:
    UI(int& argc, char** argv);
    ~UI() = default;

    void showMainWindow();
    int RunExec();
};

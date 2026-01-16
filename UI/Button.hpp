#pragma once

#include <QObject>
#include <QPushButton>
#include <memory>
#include <string>

#include "../Core/Gameplay/Gameplay.hpp"

class Button : public QObject
{
private:
    Q_OBJECT

protected:
    std::unique_ptr<QPushButton> button = nullptr;

    void onClicked();

public:
    Button(const std::string& text);
    std::unique_ptr<QPushButton>& getButton();

};

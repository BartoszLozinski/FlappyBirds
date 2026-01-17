#pragma once

#include <QObject>
#include <QPushButton>
#include <memory>
#include <string>

class IButton : public QObject
{
protected:
    Q_OBJECT
    std::unique_ptr<QPushButton> button = nullptr;

    virtual void OnClicked() = 0;

public:
    IButton(const std::string& text);
    virtual ~IButton() = default;
    std::unique_ptr<QPushButton>& GetButton();

};

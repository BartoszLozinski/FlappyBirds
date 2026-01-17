#include "Button.hpp"

IButton::IButton(const std::string& text)
    : button(std::make_unique<QPushButton>(QString::fromStdString(text)))
{
    connect(button.get(), &QPushButton::clicked, this, &IButton::OnClicked);
};

std::unique_ptr<QPushButton>& IButton::GetButton()
{
    return button;
}

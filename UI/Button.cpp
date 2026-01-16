#include "Button.hpp"


void Button::onClicked()
{
    Gameplay gameplay{};
    gameplay.Run();
}


Button::Button(const std::string& text)
    : button(std::make_unique<QPushButton>(QString::fromStdString(text)))
{
    connect(button.get(), &QPushButton::clicked, this, &Button::onClicked);
};

std::unique_ptr<QPushButton>& Button::getButton()
{
    return button;
}

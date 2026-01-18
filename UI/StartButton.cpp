#include "StartButton.hpp"

#include "../Core/Gameplay/Session.hpp"

StartButton::StartButton(const std::string& text)
    : IButton(text)
{};

void StartButton::OnClicked()
{
    Gameplay::Session{}.Run();
}

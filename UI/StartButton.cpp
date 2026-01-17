#include "StartButton.hpp"

#include "../Core/Gameplay/Gameplay.hpp"

StartButton::StartButton(const std::string& text)
    : IButton(text)
{};

void StartButton::OnClicked()
{
    Gameplay{}.Run();
}

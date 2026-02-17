#include "StartCVSessionButton.hpp"

#include "../ComputerVision/CVSession.hpp"

StartCVSessionButton::StartCVSessionButton(const std::string& text)
    : IButton(text)
{};

void StartCVSessionButton::OnClicked()
{
    Gameplay::CVSession{}.Run();
}

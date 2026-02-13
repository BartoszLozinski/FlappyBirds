#include "StartAIGameButton.hpp"

#include "../MachineLearning/AIDrivenSession.hpp"

StartAIGameButton::StartAIGameButton(const std::string& text)
    : IButton(text)
{};

void StartAIGameButton::OnClicked()
{
    Gameplay::AIDrivenSession{}.Run();
}

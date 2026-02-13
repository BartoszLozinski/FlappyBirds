#pragma once

#include "Button.hpp"

class StartAIGameButton : public IButton
{
protected:
    void OnClicked() override final;

public:
    StartAIGameButton(const std::string& text);

};

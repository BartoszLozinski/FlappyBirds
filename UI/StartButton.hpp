#pragma once

#include "Button.hpp"

class StartButton : public IButton
{
protected:
    void OnClicked() override final;

public:
    StartButton(const std::string& text);

};

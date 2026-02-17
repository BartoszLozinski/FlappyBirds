#pragma once

#include "Button.hpp"

class StartCVSessionButton : public IButton
{
protected:
    void OnClicked() override final;

public:
    StartCVSessionButton(const std::string& text);

};

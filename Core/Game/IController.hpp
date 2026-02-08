#pragma once

#include "Utils/ControlOption.hpp"
#include "Gameplay/State.hpp"

class IController
{
protected:
    ControlOption controlOption = ControlOption::None;

public:
    virtual ~IController() = default;
    [[nodiscard]] virtual ControlOption Decide() const = 0;
};

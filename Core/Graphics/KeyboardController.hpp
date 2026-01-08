#pragma once

#include "Utils/ControlOption.hpp"

namespace Graphics
{
    class KeyboardController
    {
    private:
        bool jumpPressed = false;
        void JumpPressed();
        
    public:

        ControlOption GetControlOption();
        inline void ResetState() {jumpPressed = false; };
    };
}

#pragma once

#include <array>
#include <span>

#include "Moveable.hpp"
#include "Utils/Utils.hpp"

namespace Game
{
    class Pipe : public Moveable
    {
    protected:

    public:
        Pipe(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
        void UpdateState() override;

        [[nodiscard]] bool MovedOutOfTheWindow() const;
        void ResetPosition(const bool movedOutOfTheWindow);
    };

    class Pipes
    {
    private:
        static constexpr int horizontalDistanceBetweenPipes = 400;
        static constexpr int verticalDistanceBetweenPipes = 300;
        static constexpr unsigned horizontalSize = 50;
        static constexpr unsigned verticalSize = 500;
        static constexpr int outOfWindowOverlap = -100;

        std::array<Pipe, 2> pipes;
    public:

        Pipes();
        void UpdateState();
        std::span<const Pipe> GetPipes() const;

    };
}
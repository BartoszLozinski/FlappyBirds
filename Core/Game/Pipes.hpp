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
        void SetPosition(const Utils::Vector2f& position_);
    };

    class Pipes
    {
    private:
        static constexpr int horizontalDistanceBetweenPipes = 400;
        static constexpr int verticalDistanceBetweenPipes = 200;
        static constexpr unsigned horizontalSize = 80;
        static constexpr unsigned verticalSize = 500;
        static constexpr int outOfWindowOverlap = -100;

        std::array<Pipe, 2> pipes;

        void VerticalShift();

    public:
        Pipes();
        ~Pipes() = default;
        Pipes(const Pipes&) = delete;
        Pipes(Pipes&&) = delete;
        Pipes& operator=(const Pipes&) = delete;
        Pipes& operator=(Pipes&&) = delete;

        void UpdateState();
        std::span<const Pipe> GetPipes() const;

    };
}
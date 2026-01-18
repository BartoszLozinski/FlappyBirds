#pragma once

#include <array>
#include <span>
#include <memory>

#include "Moveable.hpp"
#include "Utils/Utils.hpp"

namespace Game
{
    enum class PipesSegmentIndex
    {
        Top = 0,
        Bottom = 1,
    };

    class Pipe : public Moveable
    {
    protected:

    public:
        Pipe(const Utils::Vector2u& size_, const Utils::Vector2f& position_);
        void UpdateState() override;

        [[nodiscard]] bool MovedOutOfTheWindow() const;
        void ResetPosition(const bool movedOutOfTheWindow, const float xPosition);
        void SetPosition(const Utils::Vector2f& position_);
    };

    class Pipes
    {
    private:
        static constexpr unsigned horizontalSize = 80;
        static constexpr unsigned verticalSize = 500;
        static constexpr int outOfWindowOverlap = -50;
        std::array<Pipe, 2> pipesSegment;
        bool isScored = false;

        void VerticalShift();
    public:
        static constexpr int verticalDistanceBetweenPipes = 200;
        
        Pipes();
        Pipes(const float xPosition);
        ~Pipes() = default;
        Pipes(const Pipes&) = delete;
        Pipes(Pipes&&) = delete;
        Pipes& operator=(const Pipes&) = delete;
        Pipes& operator=(Pipes&&) = delete;

        void UpdateState();
        std::span<const Pipe> GetPipesSegment() const;
        void ResetPosition(const bool movedOutOfTheWindow, const float xPosition);
        bool IsScored() const;
        void Score();
    };   
}
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
        std::array<Pipe, 2> pipesSegment;
        bool isScored = false;
        void VerticalShift(const float yPositionTop, const float yPositionBottom);

    public:

        Pipes();
        Pipes(const unsigned horizontalSize, const unsigned verticalSize, const float xPosition, const float yPositionTop, const float yPositionBottom);
        ~Pipes() = default;
        
        void UpdateState();
        std::span<const Pipe> GetPipesSegment() const;
        void ResetPosition(const bool movedOutOfTheWindow, const float xPosition, const float yPostionTop, const float yPositionBottom);
        bool IsScored() const;
        void Score();
    };   
}
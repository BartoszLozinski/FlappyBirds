#pragma once

#include "Game/Pipes.hpp"

namespace Game
{
    class Environment
    {
    private:
        static constexpr unsigned horizontalSize = 80;
        static constexpr unsigned verticalSize = 500;
        static constexpr int outOfWindowOverlap = -50;
        static constexpr float minVerticalShift = -150;
        static constexpr float maxVerticalShift = 150;
        static constexpr int horizontalDistanceBetweenPipes = 200;
        static constexpr int verticalDistanceBetweenPipes = 200;

        Utils::RandomGenerator<float> randomGenerator{minVerticalShift, maxVerticalShift};
        std::vector<std::unique_ptr<Pipes>> pipes;
        bool isStopped = false;

    public: 
        Environment();
        ~Environment() = default;
        Environment(const Environment&) = delete;
        Environment(Environment&&) = delete;
        Environment& operator=(const Environment&) = delete;
        Environment& operator=(Environment&&) = delete;

        std::span<const std::unique_ptr<Pipes>> GetPipes() const;
        static inline int GetVerticalDistanceBetweenPipes() { return verticalDistanceBetweenPipes; }
        void UpdateState();
        void Stop();
    };
}
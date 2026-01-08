#pragma once

#include "Game/Pipes.hpp"

namespace Game
{
    class Environment
    {
    private:
        static constexpr int horizontalDistanceBetweenPipes = 200;
        std::vector<std::unique_ptr<Pipes>> pipes;

    public: 
        Environment();
        ~Environment() = default;
        Environment(const Environment&) = delete;
        Environment(Environment&&) = delete;
        Environment& operator=(const Environment&) = delete;
        Environment& operator=(Environment&&) = delete;

        void UpdateState();
        std::span<const std::unique_ptr<Pipes>> GetPipes() const;
    };
}
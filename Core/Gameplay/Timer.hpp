#pragma once

#include <chrono>

class Timer
{
private:
    using clock = std::chrono::steady_clock;
    using ms = std::chrono::milliseconds;

    clock::time_point startTime = clock::now();
    int64_t period = 0;

public:
    Timer() = delete;
    Timer(const int64_t period_);
    ~Timer() = default;

    int64_t TimeElapsed() const;
    [[nodiscard]] bool IsExpired();
    void Reset();
};

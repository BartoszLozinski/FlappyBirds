#include "Timer.hpp"

namespace Gameplay
{
    Timer::Timer(const int64_t period_)
        : period(period_)
    {};

    int64_t Timer::TimeElapsed() const
    {
        return std::chrono::duration_cast<ms>(clock::now() - startTime).count();
    }

    void Timer::Reset()
    {
        startTime = clock::now();
    }

    bool Timer::IsExpired()
    {
        if (TimeElapsed() >= period)
            return true;
            
        return false;
    }
}

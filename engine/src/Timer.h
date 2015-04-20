#pragma once

#include <chrono>

namespace pdEngine
{

class Timer
{
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Duration = std::chrono::high_resolution_clock::duration;

public:
    static inline TimePoint now() noexcept;

public:
    Timer(const int stepsPerSecond);
    virtual ~Timer() = default;

    bool stepAndSleep(void);

    inline bool step(void) noexcept;
    int getStepDeltaMs(void) const noexcept;

    unsigned long totalMicro(void) const;
    unsigned long totalMilli(void) const;
    unsigned long totalSeconds(void) const;

private:
    TimePoint start;
    TimePoint prev;
    Duration timeSlice;
};

/*
 * Implementations
 */

auto Timer::now() noexcept -> TimePoint
{
    return std::chrono::high_resolution_clock::now();
}

bool Timer::step(void) noexcept
{
    if (prev > now()) return false;

    prev+=timeSlice;
    return true;
}

}


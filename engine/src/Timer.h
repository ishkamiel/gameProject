#pragma once

#include <chrono>

namespace pdEngine
{

class Timer
{
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Duration = std::chrono::high_resolution_clock::duration;

    TimePoint start;
    TimePoint prev;
    Duration timeSlice;
    int m_delta;

public:
    static inline TimePoint now() noexcept;

    Timer(const int stepsPerSecond);
    virtual ~Timer() = default;

    /**
     * @brief Checks whether it's time to execute another step.
     */
    inline bool step(void) noexcept;

    /**
     * @brief Retrieves the delta time for each time step. Provided the timer frequency is
     * unaltered this will always be the same value.
     */
    inline int getStepDeltaMs(void) const noexcept;

    unsigned long totalMicro(void) const;
    unsigned long totalMilli(void) const;
    unsigned long totalSeconds(void) const;
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

int Timer::getStepDeltaMs(void) const noexcept
{
    return m_delta;
}



}


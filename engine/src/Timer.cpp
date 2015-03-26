#include "Timer.h"

#include <chrono>

namespace pdEngine
{
    Timer::Timer(TimerFrequency freq)
        : prev(std::chrono::high_resolution_clock::now()), frequency(freq)
    {}

    Timer::step()
    {
        delta = now()-prev;
        prev += delta;
    }
}

#include "Timer.h"

#include "Logger.h"
#include "Memory.h"

#include <chrono>
#include <thread>

#include <boost/log/trivial.hpp>

namespace pdEngine
{
Timer::Timer(int freq)
    : start(std::chrono::high_resolution_clock::now()), prev(start)
{
    m_delta = 1000 / freq;
    timeSlice = std::chrono::duration_cast<Duration>(std::chrono::milliseconds(m_delta));

    if (m_delta * freq != 1000) {
        PDE_WARN << "1000ms not divisible by given frequency " << freq;
    }

    PDE_DEBUG << "Updates per second set to " << freq << ", milliseconds per update: " << timeSlice.count();
}

unsigned long Timer::totalMicro(void) const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(now() - start).count();
}

unsigned long Timer::totalMilli(void) const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(now() - start).count();
}

unsigned long Timer::totalSeconds(void) const
{
    return (std::chrono::duration_cast<std::chrono::seconds>(now() - start)).count();
}

}

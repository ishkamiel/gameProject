#include "Timer.h"

#include <chrono>
#include <thread>

namespace pdEngine
{
    Timer::Timer(TimerFrequency freq)
        : prev(std::chrono::high_resolution_clock::now())
    {
        setFrequencey(freq);
    }

    TimerDefaultDelta Timer::setFrequencey(TimerFrequency freq)
    {
        std::chrono::seconds oneSec {1};
        TimerDefaultDelta timeSlice = 
            std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(oneSec);

        timeSlice = timeSlice / freq;
        return timeSlice;
    }

    TimeDelta Timer::step()
    {
        std::this_thread::sleep_for( timeSlice + prev - diff - now());
        delta = now()-prev;
        prev += delta;

        return std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count();
    }
}

#include "Timer.h"

#include "Logger.h"
#include "Utils.h"

#include <chrono>
#include <thread>

namespace pdEngine
{
    Timer::Timer(TimerFrequency freq)
        : prev(std::chrono::high_resolution_clock::now()) 
    {
        start = prev;

        std::chrono::seconds oneSec {1};
        timeSlice = std::chrono::duration_cast<TimerDefaultDelta>(oneSec);

        timeSlice = (timeSlice/freq);
        DLOG("Frequency set to {0}, resulting in a {1} timeSlice", freq, timeSlice.count());
    }

    /*
    TimerDefaultDelta Timer::setFrequencey(TimerFrequency freq)
    {
        std::chrono::seconds oneSec {1};
        timeSlice = std::chrono::duration_cast<TimerDefaultDelta>(oneSec);

        timeSlice = (timeSlice/freq);
        DLOG("Frequency set to {0}, resulting in a {1} timeSlice", freq, timeSlice.count());
        return timeSlice;
    }
    */

    TimeDelta Timer::stepAndSleep(void)
    {
        auto sleepTime = timeSlice - (now() - prev);
        if (sleepTime.count() > 0)
            std::this_thread::sleep_for(sleepTime);

        delta = now()-prev;
        prev += delta;

        return delta.count();
        //return std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
    }

    TimeMicro Timer::totalMicro(void) const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(prev-start).count();
    }

    TimeMilli Timer::totalMilli(void) const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(prev-start).count();
    }

    TimeSeconds Timer::totalSeconds(void) const
    {
        return (std::chrono::duration_cast<std::chrono::seconds>(prev-start)).count();
    }

    TimeMicro Timer::deltaMicro(void) const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
    }

    TimeMilli Timer::deltaMilli(void) const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
    }

    TimeSeconds Timer::deltaSeconds(void) const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(delta).count();
    }
}

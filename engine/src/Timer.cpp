#include "Logger.h"
#include "Timer.h"

#include <chrono>
#include <thread>

namespace pdEngine
{
    Timer::Timer(TimerFrequency freq)
        : prev(std::chrono::high_resolution_clock::now()) 
    {
        start = prev;
        setFrequencey(freq);
    }

    TimerDefaultDelta Timer::setFrequencey(TimerFrequency freq)
    {
        std::chrono::seconds oneSec {1};
        timeSlice = std::chrono::duration_cast<TimerDefaultDelta>(oneSec);

        timeSlice = (timeSlice/freq);
        DLOG("Frequency set to {0}, resulting in a {1} timeSlice", freq, timeSlice.count());
        return timeSlice;
    }

    TimeDelta Timer::stepAndSleep()
    {
        auto sleepTime = timeSlice - (now() - prev);
        if (sleepTime.count() > 0)
            std::this_thread::sleep_for(sleepTime);

        auto t = now();

        delta = t-prev;

        // DLOG("Thread sleeping for {0} nanosecs", sleepTime.count());
        
        delta = now()-prev;
        prev += delta;

        return std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count();
    }

    TimeMilliseconds Timer::totalMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(now()-start).count();
    }

    TimeSeconds Timer::totalSeconds()
    {
        return (std::chrono::duration_cast<std::chrono::seconds>(now()-start)).count();
    }
}

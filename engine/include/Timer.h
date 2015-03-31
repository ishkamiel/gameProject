#ifndef PDENGINE_TIMER_H_
#define PDENGINE_TIMER_H_

#include <chrono>

namespace pdEngine
{
    using TimeDelta = unsigned long int;
    using TimeMilliseconds = unsigned int;
    using TimeSeconds = unsigned int;

    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using TimerDefaultDelta = std::chrono::high_resolution_clock::duration;
    using TimerFrequency = unsigned int;

    static inline TimePoint now();

    class Timer
    {
        TimePoint           start;
        TimePoint           prev;
        TimerDefaultDelta   delta;
        TimerDefaultDelta   diff;
        TimerDefaultDelta   timeSlice;

    public:
        Timer(TimerFrequency stepsPerSecond);
        TimeDelta stepAndSleep();
        TimerDefaultDelta setFrequencey(TimerFrequency);

        TimeMilliseconds totalMilliseconds();
        TimeSeconds totalSeconds();

    private:
    };
}

namespace pdEngine
{
    TimePoint now() 
    {
        return std::chrono::high_resolution_clock::now();
    }
}
    

#endif /* PDENGINE_TIMER_H_ */

#ifndef PDENGINE_TIMER_H_
#define PDENGINE_TIMER_H_

#include <chrono>

namespace pdEngine
{
    using TimeMicro = unsigned long int;
    using TimeMilli = unsigned long int;
    using TimeSeconds = unsigned int;

    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using TimerDefaultDelta = std::chrono::high_resolution_clock::duration;
    using TimerFrequency = unsigned int;

    using TimeDelta = std::chrono::high_resolution_clock::duration;

    static inline TimePoint now();

    class Timer
    {
        TimePoint           start;
        TimePoint           prev;
        TimerDefaultDelta   delta;
        TimerDefaultDelta   timeSlice;

    public:
        Timer(const TimerFrequency stepsPerSecond);
        TimeMicro stepAndSleep(void);

        // TimeNanoseconds deltaNanoseconds(void) const;
        // TimeMilliseconds deltaMilliseconds(void) const;
        // TimeSeconds deltaSeconds(void) const;

        TimeMicro  totalMicro(void) const;
        TimeMilli totalMilli(void) const;
        TimeSeconds totalSeconds(void) const;

        TimeMicro  deltaMicro(void) const;
        TimeMilli deltaMilli(void) const;
        TimeSeconds deltaSeconds(void) const;

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

#ifndef PDENGINE_TIMER_H_
#define PDENGINE_TIMER_H_

#include <chrono>

namespace pdEngine
{
    using TimeDelta = unsigned long int;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using TimerDefaultDelta = std::chrono::high_resolution_clock::duration;
    using TimerFrequency = unsigned int;

    static inline TimePoint now();

    class Timer
    {
        TimePoint           prev;
        TimerDefaultDelta   delta;
        TimerDefaultDelta   diff;
        TimerDefaultDelta   timeSlice;

    public:
        Timer(TimerFrequency);
        TimeDelta step();
        TimerDefaultDelta setFrequencey(TimerFrequency);

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

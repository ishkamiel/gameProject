#ifndef PDENGINE_TIMER_H_
#define PDENGINE_TIMER_H_

#include <chrono>

namespace pdEngine
{
    using TimeDelta = unsigned long int;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    static inline TimePoint now();

    class Timer
    {
        using TimerDefaultDelta = std::chrono::high_resolution_clock::duration;
        using TimerFrequency = unsigned int;

        TimePoint prev;
        TimerDefaultDelta delta;
        TimerFrequency frequency;
    public:
        Timer(TimerFrequency);
        void step();
        inline TimeDelta getTimeDelta();

    private:
    };
}

namespace pdEngine
{
    TimePoint now() 
    {
        return std::chrono::high_resolution_clock::now();
    }


    inline TimeDelta Timer::getTimeDelta()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count();
    }
}
    

#endif /* PDENGINE_TIMER_H_ */

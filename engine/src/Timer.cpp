#include "Timer.h"

#include "Logger.h"
#include "Utils.h"

#include <chrono>
#include <thread>

#include <boost/log/trivial.hpp>

namespace pdEngine
{
Timer::Timer(int freq)
    : start(std::chrono::high_resolution_clock::now()), prev(start)
{
    std::chrono::seconds oneSec {1};
    timeSlice = std::chrono::duration_cast<Duration>(oneSec);

    timeSlice = (timeSlice/freq);
    /*
    rest = timeSlice - std::chrono::duration_cast<Duration>(
        std::chrono::milliseconds(getStepDeltaMs()));
	*/

    PDE_DEBUG << "Updates per second set to " << freq << ", milliseconds per update: " << timeSlice.count();
}

int Timer::getStepDeltaMs(void) const noexcept
{
	 return std::chrono::duration_cast<std::chrono::milliseconds>(timeSlice).count();
}


bool Timer::stepAndSleep(void)
{
    //auto sleepTime = timeSlice - (now() - prev);
    //if (sleepTime.count() > 0)
        //std::this_thread::sleep_for(sleepTime);
//
    //delta = now()-prev;
    //prev += delta;

    //return delta.count();
    //return std::chrono::duration_cast<std::chrono::microseconds>(delta).count();
    return false;
}

unsigned long Timer::totalMicro(void) const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(prev-start).count();
}

unsigned long Timer::totalMilli(void) const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(prev-start).count();
}

unsigned long Timer::totalSeconds(void) const
{
    return (std::chrono::duration_cast<std::chrono::seconds>(prev-start)).count();
}

}

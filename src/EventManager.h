#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <function>

namespace pdGame
{
    EventManager getEventManager();

    class EventManager
    {
        public:
            bool AddListener(std::string event_name, std::function listener);
            bool RemoveListener(std::string event_name, std::function listener);
            void FireEvent(std::string event_name);

        private:
            EventManager();
    }
}

#endif


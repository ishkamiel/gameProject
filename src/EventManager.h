#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <memory>
#include <string>
#include <functional>

namespace pdGame
{
    class EventManager;
    class EventManagerImpl;
    std::shared_ptr<EventManager> getEventManager();


    class EventManager
    {
        public:
            bool addListener(std::string event_name, std::function<void()> listener);
            bool removeListener(std::string event_name, std::function<void()> listener);
            void fireEvent(std::string event_name);

        private:
            std::unique_ptr<EventManagerImpl> impl;
            EventManager();
            ~EventManager();
    };
}

#endif


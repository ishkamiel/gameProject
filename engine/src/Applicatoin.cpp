/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "Logger.h"

namespace pdEngine
{
    Application::Application()
    : taskManager(new TaskManager())
    {}

    Application::~Application()
    {}

    bool Application::init()
    {
        taskManager->addTask(getEventManager());
        return(true);
    }

    bool Application::start()
    {
        return(true);
    }
}


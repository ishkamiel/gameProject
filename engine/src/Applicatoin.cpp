/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

namespace pdEngine
{
	Application::Application()
	: log(pdUtils::getLogger()), taskManager(new TaskManager())
	//: taskManager(new TaskManager()), log(pdUtils::getLogger())
	{}
	
	Application::~Application()
	{}
	
	bool Application::init()
	{
		log->info("initializing application..");
		//taskManager->addTask(getEventManager());
		return(true);
	}
	
	bool Application::start()
	{
		return(true);
	}
}


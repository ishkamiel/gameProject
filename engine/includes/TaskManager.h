/*
 * TaskManager.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_TASKMANAGER_H_
#define PDENGINE_TASKMANAGER_H_

#include "General.h"

namespace pdEngine
{
	class ITask
	{
	public:
		virtual ITask() =0;
		virtual ~ITask() =0;

		virtual void v_onUpdate(timeDelta) =0;
		virtual void v_pause() {};
		virtual void v_unPause() {};
	};
}

#endif /* PDENGINE_TASKMAN_AGER_H_ */

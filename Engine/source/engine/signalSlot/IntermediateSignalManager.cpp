#include <stdafx.h>
#include <engine/signalSlot/IntermediateSignalManager.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/signalSlot/SignalTask.h>

namespace engine
{
	void IntermediateSignalManager::addTask(std::unique_ptr<ISignalTask> task)
	{
		if(!task->isExpired())
		{
			(*task)();
		}
	}
}
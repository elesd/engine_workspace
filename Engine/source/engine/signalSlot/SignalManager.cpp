#include "stdafx.h"
#include "SignalManager.h"

#include "engine/signalSlot/SignalTask.h"


namespace engine
{
	struct SignalManagerPrivate
	{
		std::deque<ISignalTask*> taskPool;
	};

	SignalManager::SignalManager()
		:_members(new SignalManagerPrivate())
	{

	}

	SignalManager::~SignalManager()
	{
		for(ISignalTask *task : _members->taskPool)
		{
			delete task;
		}
		delete _members;
	}

	void SignalManager::addTask(std::unique_ptr<ISignalTask> task)
	{
		_members->taskPool.push_back(task.get());
		task.release();
	}

	void SignalManager::update()
	{
		for(ISignalTask *task : _members->taskPool)
		{
			if(!task->isExpired())
				(*task)();
		}
		_members->taskPool.clear();
	}
}

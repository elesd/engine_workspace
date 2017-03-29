#include <stdafx.h>
#include <engine/signalSlot/SignalManager.h>

#include <engine/signalSlot/SignalTask.h>


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

	SignalManager::SignalManager(SignalManager &&o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	SignalManager &SignalManager::operator=(SignalManager &&o)
	{
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void SignalManager::addTask(std::unique_ptr<ISignalTask> task)
	{
		_members->taskPool.push_back(task.get());
		task.release();
	}

	void SignalManager::update()
	{
		auto copyOfTasks = _members->taskPool;
		_members->taskPool.clear();
		for(ISignalTask *task : copyOfTasks)
		{
			if(!task->isExpired())
				(*task)();
		}
	}
}

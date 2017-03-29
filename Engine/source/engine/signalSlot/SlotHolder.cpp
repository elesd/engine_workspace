#include <stdafx.h>

#include <engine/signalSlot/SlotHolder.h>
#include <engine/signalSlot/ISignal.h>

namespace engine
{
	struct SlotHolderPrivate
	{
		std::list<ISignal*> signals;
		bool underDistruction = false;
	};

	SlotHolder::SlotHolder()
	{
		_members = new SlotHolderPrivate();
	}

	SlotHolder::~SlotHolder()
	{
		_members->underDistruction = true;
		for(ISignal *signal : _members->signals)
		{
			signal->disconnectAllSlot(this);
		}
		delete _members;
	}

	void SlotHolder::assignSignal(ISignal *signal)
	{
		auto it = std::find(_members->signals.begin(), _members->signals.end(), signal);
		if(it == _members->signals.end())
			_members->signals.emplace_back(signal);
	}

	void SlotHolder::removeSignal(ISignal *signal)
	{
		if(_members->underDistruction)
			return;

		_members->signals.remove(signal);
	}
}
#pragma once

#include <engine/utils/IdGenerator.h>
#include <engine/signalSlot/ISignalManager.h>
#include <engine/signalSlot/SlotHolder.h>
#include <engine/signalSlot/SignalCaller.h>
#include <engine/signalSlot/SignalTask.h>

namespace engine
{

	namespace _private
	{
		struct MEMBER_FUNCTION;

		template<class T, typename ...Args>
		struct MemberFunctionId
		{
			template<void (T::*func)(Args...)>
			struct Id
			{
				static uint32_t value;
			};
		};

		template<class T, typename ...Args>
		template<void (T::*func)(Args...)>
		uint32_t MemberFunctionId<T, Args...>::Id<func>::value = engine::IdGenerator<MEMBER_FUNCTION>::generateNextId();
	}

	template<typename ...Args>
	Signal<Args...>::~Signal()
	{
		std::list<SlotHolder*> holders;
		for(Entry &entry : slots)
		{
			if(std::find(holders.begin(), holders.end(), entry.key.object) == holders.end())
			{
				holders.emplace_back(entry.key.object);
			}
		}
		for(SlotHolder *holder : holders)
		{
			holder->removeSignal(this);
		}
	}

	template<typename ...Args>
	template<class T, void (T::*slot)(Args...)>
	void Signal<Args...>::connect(T *holder)
	{
		std::function<void(Args...)> f = SignalCaller<Args...>::createCallable(holder, slot);
		std::shared_ptr<SignalCaller<Args...> >action(new SignalCaller<Args...>(f));
		using IdClass = typename engine::_private::template MemberFunctionId<T, Args...>::template Id < slot > ;
		uint32_t functionId = IdClass::value;
		Entry entry{
			action,
			holder->getSignalManager(),
			{ holder, functionId } };
		auto it = std::find(slots.begin(), slots.end(), entry);
		if(it == slots.end())
		{
			holder->assignSignal(this);
			slots.emplace_back(entry);
		}
	}

	template<typename ...Args>
	template<class T, void (T::*slot)(Args...)>
	void Signal<Args...>::disconnect(T *holder)
	{
		if(slots.empty())
			return;
		uint32_t functionId = _private::template MemberFunctionId<T, Args...>::template Id<slot>::value;
		auto it = std::remove_if(slots.begin(), slots.end(),
								 [holder, functionId](const Entry &entry)->bool
		{
			return entry.key.slotId == functionId && entry.key.object == static_cast<SlotHolder*>(holder);
		});
		if(it == slots.end())
			return;

		slots.erase(it, slots.end());

		if(!isConnected(holder))
		{
			holder->removeSignal(this);
		}
	}

	template<typename ...Args>
	template<class T>
	bool Signal<Args...>::isConnected(const T *holder) const
	{
		auto it = std::find_if(slots.begin(), slots.end(),
							   [holder](const Entry &entry)->bool{return entry.key.object == holder; });
		return it != slots.end();
	}

	template<typename ...Args>
	template<class T>
	void Signal<Args...>::disconnectAll(T *holder)
	{
		if(slots.empty())
			return;
		auto it = std::remove_if(slots.begin(), slots.end(),
								 [holder](const Entry &entry)->bool{return entry.key.object == holder; });
		HARD_ASSERT(it != slots.end());
		slots.erase(it, slots.end());

		holder->removeSignal(this);
	}

	template<typename ...Args>
	void Signal<Args...>::emit(Args... args)
	{
		for(Entry &entry : slots)
		{
			std::unique_ptr<ISignalTask> task(new SignalTask<Args...>(entry.caller, std::tuple<Args...>(args...)));
			entry.signalManager->addTask(std::move(task));
		}
	}
}

#pragma once

#include "engine/signalSlot/SignalCaller.h"

namespace engine
{
	namespace signalSlot
	{
		/**
		* Task which is created from a slot and a given member
		*/
		class ISignalTask
		{
		public:
			/** Default destructor */
			virtual ~ISignalTask() {};

			/** Execute the slot*/
			virtual void operator()() = 0;

			/** Expired if the SignalCaller has been destroyed. */
			virtual bool isExpired() const = 0;
		};

		/**
		* A signal task for the ISignalManager.
		* This class is more than a simple std::function because it cares about the object to what the function is bind.
		*/
		template<typename ...Args>
		class SignalTask : public ISignalTask
		{
		public:
			/**
			* Create a Signal task from the weak pointer to the caller and with the arguments.
			* @param caller: This caller is stored and called.
			* @param args: The caller will called with these arguments.
			*/
			SignalTask(std::weak_ptr<SignalCaller<Args...>> caller, const std::tuple<Args...> &args): object(caller)
			{
				std::shared_ptr<SignalCaller<Args...>>sharedPtr = caller.lock();
				function = std::bind(&SignalCaller<Args...>::operator(), sharedPtr.get(), args);
			}

			/**
			* Call the function caller with the stored arguments, but only if the pointer is still valid.
			*/
			void operator()() override
			{
				HARD_ASSERT(!isExpired());
				function();
			}

			/**
			* Checks whether the pointer to the caller is still valid.
			*/
			bool isExpired() const override
			{
				return object.expired();
			}
		private:
			/** Store a caller function and the arguments*/
			std::function<void()> function;

			/** Stores a weak reference to the signal caller*/
			std::weak_ptr<SignalCaller<Args...> >object;
		};
	}
}

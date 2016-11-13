#pragma once

#include "engine/signalSlot/SignalCaller.h"
#include "engine/signalSlot/ISignal.h"

#define CONNECT_SIGNAL(o1, signal, o2, slot) (o1)->signal.connect<std::remove_pointer<decltype(o2)>::type, &std::remove_pointer<decltype(o2)>::type::slot>(o2);
#define DISCONNECT_SIGNAL(o1, signal, o2, slot) (o1)->signal.disconnect<std::remove_pointer<decltype(o2)>::type, &std::remove_pointer<decltype(o2)>::type::slot>(o2);

namespace engine
{
	namespace signalSlot
	{
		class ISignalManager;
		class SlotHolder;
		/**
		 * This class implements a signal.
		 * A signal can be emitted in this case all the slots will be called. The call is depend on
		 * the slot's signalManager.
		 * @tparam Args: Signature of the signal.
		*/
		template<typename ...Args>
		class Signal final : public ISignal
		{
		private:

			/**
			  When a signal emitted a task is created for all of the connected slots.
			  These tasks are stired in this entry.
			*/
			struct Entry
			{
				using MemberFunctionId = uint32_t;
				/** Pointer to the caller. This caller will call the corresponding slot.
				* It must be a shared pointer because of the disconnect possibilities.
				*/
				std::shared_ptr<SignalCaller<Args...>> caller;

				/** Signal manager of the slot's holder*/
				ISignalManager *signalManager;

				struct
				{
					/** Pointer to the slot*/
					SlotHolder *object;
					/** Unique id of the slot member function*/
					MemberFunctionId slotId;
				} key; /**< Unique key of a entry*/

				/**
				* Two Entry is compared by the key.
				* @param o other object
				*/
				bool operator==(const Entry &o) { return o.key.slotId == key.slotId && o.key.object == key.object; }
			};

			using EntryCollection = typename std::list<Entry>;
		public:
			/** Defualt constructor.*/
			Signal() = default;

			/** Notify all connected slot*/
			~Signal() override;

			/**
			 * Connect the holder member function to this signal.
			 * When the signal is emitted a task will crated which will call this member function on the given object.
			 * @tparam slot: Slot to connect to this signal
			 * @param holder: owner of the slot.
			*/
			template<class T, void (T::*slot)(Args...)>
			void connect(T *holder);

			/**
			* Disconnect the given slot and object from this signal. Via the shared pointer all the created tasks are
			* invalidated.
			* @tparam slot: Slot to disconnect to this signal
			* @param holder: owner of the slot.
			*/
			template<class T, void (T::*slot)(Args...)>
			void disconnect(T *holder);

			/**
			* Disconnect all the slots of the given slot holder
			* @param holder: owner of the slot
			*/
			template<class T>
			void disconnectAll(T *holder);

			/**
			* Emit the signal.
			* For all the connected slot a task is created and added to the corresponding signal manager.
			*/
			void emit(Args&&... args);

		private:
			void disconnectAllSlot(SlotHolder *slotHolder) override { disconnectAll(slotHolder); }

			template<class T>
			bool isConnected(const T *holder) const;
		private:
			/**
			* Connected slots.
			*/
			EntryCollection slots;
		};
	}
}

#include "engine/signalSlot/Signal.hpp"

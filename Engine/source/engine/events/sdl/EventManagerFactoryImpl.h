#pragma once

#include <engine/events/EventManagerFactory.h>

namespace engine
{
	namespace sdl
	{
		/**Sdl specific implementation of the event manager factory.*/
		class EventManagerFactoryImpl : public EventManagerFactory
		{
			friend class EventBuilder;
			/**@copydoc EventManagerFactory::EventManagerFactory*/
			EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs);
		private:
			/**@return Returns the sld mouse.*/
			std::unique_ptr<EventSourceBase> createMouse() const override;
			/**@return Returns the sld keyboard.*/
			std::unique_ptr<EventSourceBase> createKeyboard() const override;
			/**@return Returns the sld event manager.*/
			std::unique_ptr<EventManager> createEventManagerImpl() override;
		};
	}
}

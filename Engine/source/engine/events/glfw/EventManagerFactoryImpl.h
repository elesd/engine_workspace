#pragma once

#include <engine/events/EventManagerFactory.h>

namespace engine
{
    class EventBuilder;
	namespace glfw
	{
		/**Glfw EventManagerFactory implemenetation.*/
		class EventManagerFactoryImpl : public EventManagerFactory
		{
			friend class engine::EventBuilder;
			/**@copydoc EventManagerFactory::EventManagerFactory*/
			EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs);
		private:

			/** @return Returns a glfw mouse.*/
			std::unique_ptr<EventSourceBase> createMouse() const override;
			/** @return Returns a glfw Keyboard.*/
			std::unique_ptr<EventSourceBase> createKeyboard() const override;
			/** @return Returns a glfw event manager.*/
			std::unique_ptr<EventManager> createEventManagerImpl() override;
		};
	}
}

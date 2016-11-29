#pragma once

#include "engine/constraints/NonCopyable.h"
#include "engine/view/Window.h"
#include "engine/app/IApplicationParameter.h"

namespace engine
{
	namespace app
	{
		class IMain;
	}
	namespace view
	{
		struct WindowParameter;
	}
	namespace stateStack
	{
		class StateStack;
	}

}

namespace engine
{
	namespace app
	{
		/**
		* Class for the application main logic.
		*/
		class Application: engine::constraints::NonCopyable
		{
		public:
			/**
			* Create an application with the given arguments.
			* @param arguments: Application arguments, tipically forwarded from tha main function.
			* @param main: Application core logic.
			*/
			Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			/**Simple destructor for PIMPL*/
			~Application()  override;

			/**
			* Update is called once per each frame
			*/
			void update();
			/**
			* Render is called in each frame. Here will be rendered the application
			*/
			void render();

			/**
			* @return Returns true till the application is not terminated.
			*/
			bool isActive() const;

			/**
			* Starts the application.
			*/
			void stop();
			/**
			* Terminate the application
			*/
			void start();

			/**
			* @return Returns the initial arguments of the application
			*/
			const IApplicationParameter *getArguments() const;
		private:
			/**PIMPL*/
			struct ApplicationPrivate *_members = nullptr;
		};
	}
}

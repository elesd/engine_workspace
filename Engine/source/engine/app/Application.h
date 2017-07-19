#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/view/Window.h>
#include <engine/app/IApplicationParameter.h>


namespace engine
{
	class EventManager;
	class EventManagerFactory;
	class FileSystem;
	class IMain;
	class StateStack;
	class WindowManager;
	struct WindowParameter;

	/**
	* Class for the application main logic.
	*/
	class Application : private NonCopyable
	{
		friend class BaseBuilder;
	public:
		/**
		* Create an application with the given arguments.
		* @param arguments: Application arguments, tipically forwarded from tha main function.
		* @param main: Application core logic.
		*/
		Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
		/**Simple destructor for PIMPL*/
		virtual ~Application();

		/** Start the application and run it till it won't be stopped.*/
		void run();

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
		* Terminate the application
		*/
		void stop();
		/**
		* Starts the application.
		*/
		void start();

		/**
		* @return Returns the initial arguments of the application
		*/
		const IApplicationParameter* getArguments() const;

		/**
		* @return Returns the window manager of the application
		*/
		WindowManager* getWindowManager() const;

		/**
		* @return Returns the event manager factory of the application.
		*/
		EventManagerFactory* getEventManagerFactory() const;

		FileSystem* getFileSystem() const;

	private:
		/**
		* Setter for the Builder in order to setup window manager.
		* @see WindowBuilder
		*/
		void setWindowManager(std::unique_ptr<WindowManager> windowManager);
        void setEventManagerFactory(std::unique_ptr<EventManagerFactory> &&factory);
		void setFileSystem(std::unique_ptr<FileSystem> &&fileSystem);
	private:
		/**
		* Update function before done any other update.
		*/
		virtual void updateImpl() = 0;
	private:
		/**PIMPL*/
		struct ApplicationPrivate *_members = nullptr;
	};
}

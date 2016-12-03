#pragma once

#include "engine/constraints/Singleton.h"

namespace engine
{
	class Application;
	class WindowManager;
	class BaseBuilder;
	class Driver;

	/**
	* Engine's context.
	* This class contains the members which are necessary from everywhere in the application.
	*/
	class Context : public Singleton < Context >
	{
	private:
		using Base = Singleton < Context > ;

		friend class BaseBuilder;
		friend Base;
		/**
		* Creation is possible only by the singleton.
		*/
		Context();
	public:
		virtual ~Context() override;
		/**
		* @return Returns the current appliation.
		* @see Application
		*/
		Application *getApplication();

		/**
		* @return Returns the application window manager.
		* @see WindowManager
		*/
		WindowManager *getWindowManager();

	protected:
		/**
		* The context can be used only if it is initialized.
		* Because the context creation is a complicated task, it is done in
		* separate steps by builders.
		*/
		bool isInitialized() const;
	private:
		/**
		* Setter for builders.
		*/
		void setApplication(std::unique_ptr<Application>);
		/**
		* Setter for builders.
		*/
		void setWindowManager(std::unique_ptr<WindowManager>);
		/**
		* There are different moduls in the engine.
		* There is an array which contains which modules are initialized.
		* @return Returns the array of modules.
		*/
		std::vector<bool> &getModuls();

		/**
		* Setter for builders.
		*/
		void setInitialized();
	private:
		/** PIMPL */
		struct ContextPrivate *_members = nullptr;
	};
}

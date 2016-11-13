#pragma once

#include "engine/constraints/Singleton.h"

namespace engine
{
	namespace app
	{
		class Application;
	}
	namespace view
	{
		class WindowManager;
	}
	namespace environmentBuilder
	{
		class BaseBuilder;
	}

	/**
	* Engine's context.
	* This class contains the members which are necessary from everywhere in the application.
	*/
	class Context: public constraints::Singleton<Context>
	{
	private:
		using Base = constraints::Singleton<Context>;

		friend class environmentBuilder::BaseBuilder;
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
		app::Application *getApplication();

		/**
		* @return Returns the application window manager.
		* @see WindowManager
		*/
		view::WindowManager *getWindowManager();
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
		void setApplication(std::unique_ptr<app::Application>);
		/**
		* Setter for builders.
		*/
		void setWindowManager(std::unique_ptr<view::WindowManager>);
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

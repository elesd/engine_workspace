#pragma once

#include <engine/constraints/Singleton.h>

namespace engine
{
	class Application;
	class BaseBuilder;
	struct IModuleExtension;
	/**
	* Engine's context.
	* This class contains the members which are necessary from everywhere in the application.
	*/
	class Context : public Singleton<Context>
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
		~Context() override;
		/**
		* @return Returns the current appliation.
		* @see Application
		*/
		Application *getApplication();
	protected:
		/**
		* The context can be used only if it is initialized.
		* Because the context creation is a complicated task, it is done in
		* separate steps by builders.
		*/
		bool isInitialized() const;

	private:

		Application *getApplicationUnsafe();

		/**
		* Setter for builders.
		*/
		void setApplication(std::unique_ptr<Application>);
		
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

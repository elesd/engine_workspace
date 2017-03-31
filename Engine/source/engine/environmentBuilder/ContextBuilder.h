#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>


namespace engine
{
	enum class ContextModuleType;

	class ApplicationBuilder;
	class GameBuilder;

	/**
	* Creates the context which is the cornerstone of the environment
	*/
	class ContextBuilder : public BaseBuilder
	{
	public:
		/**
		* Create the context.
		* This build phase will also initialize the different kind of modules.
		* @param moduls: Modules which will be initialized during the build.
		*/
		ContextBuilder(const std::vector<ContextModuleType> &moduls);

		/**Moveable*/
		ContextBuilder(ContextBuilder &&o);

		/**Destructor for PIMPL*/
		~ContextBuilder();

		/**
		* Build the context and init the next step.
		* @return Returns the next building phase.
		*/
		ApplicationBuilder buildForApplication();

	private:
		/**
		* Initializes the given module.
		* @param type: The module.
		*/
		void initModule(const ContextModuleType type);

		/**
		* Initilizes the context.
		*/
		void initContext();

	private:
		/**PIMPL*/
		struct ContextBuilderPrivate *_members = nullptr;
	};
}

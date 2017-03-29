#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>

namespace engine
{
	class IMain;
	class IApplicationParameter;
	class EventBuilder;
	class Application;
	enum class ContextModuleType;

}

namespace engine
{
	/**
	* This is the application building phase.
	* After this build phase the context will have an application
	*/
	class ApplicationBuilder : public BaseBuilder
	{
	private:
		friend class ContextBuilder;
	private:
		/**
		* Construct the builder.
		* For the next step initialization we need the window module.
		* @param windowModul: Window module of the context which will be used.
		*/
		ApplicationBuilder(const ContextModuleType windowModule);
	public:
		~ApplicationBuilder();

		ApplicationBuilder(ApplicationBuilder&& o);

		/**
		* Build an application with the given arguments and main.
		* @param arguments: arguments of the application
		* @param main: Main functionality.
		* @return The next building phase.
		*/
		EventBuilder build(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
	private:
		std::unique_ptr<Application> createApplication(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
		
	private:
		/** PIMPL */
		struct ApplicationBuilderPrivate *_members = nullptr;
	};
}

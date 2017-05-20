#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

// Include for the BasicInputType enum to make easier to engine build process
#include <engine/environmentBuilder/EventBuilder.h>
namespace engine
{
	class IMain;
	class IApplicationParameter;
	class Application;
	struct FileSystemSettings;
	enum class BasicInputType;
	enum class ContextModuleType;

	/**
	* All in one builder which calls the different builder steps and creates an application and engine context.
	*/
	class EasyBuilder: NonCopyable, NonMoveable
	{
	public:
		/**
		* Construct, needs a main object.
		* @param main: The class which controls the logic of the application
		* @param windowModul: The used window module. It must be consecutive with the build engine call, i.e.: winapi cannot start with GNU main parameters.
		*/
		explicit EasyBuilder(std::unique_ptr<IMain> &&main, engine::ContextModuleType windowModul);
		/**PIMPL*/
		~EasyBuilder();

		/**
		* Add an input for the context.
		* @return Returns a reference to this to be able to do call chain.
		*/
		EasyBuilder& AddInput(engine::BasicInputType);

		void setFileSystemSetting(const FileSystemSettings &settings);

		/**
		* One step build for the engine in case of winapi application.
		* @param hInstance: Application arg.
		* @param hPrevInstance: Application arg.
		* @param lpCmdLine: Application arg.
		* @param nCmdShow: Application arg.
		* @return returns the application of the context
		*/
		Application* buildEngine(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine,
						 int nCmdShow) const;
		/**
		* One step build for the engine in case of unix application
		* @param argv: Application arg.
		* @param argc: Application arg.
		* @return returns the application of the context
		*/
		Application* buildEngine(int argc, char* argv[]) const;
	private:
		/**
		* Build the engine with the application;
		* @param args: Application args.
		*/
		void buildEngine(std::unique_ptr<IApplicationParameter> args) const;
	private:
		/**PIMPL*/
		struct EasyBuilderPrivate *_members = nullptr;
	};
}

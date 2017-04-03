#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/environmentBuilder/EventBuilder.h>

namespace engine
{
	class IMain;
	class IApplicationParameter;
	class Application;

	class EasyBuilder: NonCopyable, NonMoveable
	{
	public:
		explicit EasyBuilder(std::unique_ptr<IMain> &&main);
		~EasyBuilder();

		EasyBuilder& AddInput(engine::EventBuilder::BasicInputType);

		Application* buildEngine(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine,
						 int nCmdShow) const;
		Application* buildEngine(int argc, char* argv[]) const;
	private:
		void buildEngine(std::unique_ptr<IApplicationParameter> args) const;
	private:
		struct EasyBuilderPrivate *_members = nullptr;
	};
}
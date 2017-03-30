#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/environmentBuilder/EventBuilder.h>

namespace engine
{
	class IMain;
	class IApplicationParameter;

	class EasyBuilder: NonCopyable, NonMoveable
	{
	public:
		explicit EasyBuilder(std::unique_ptr<IMain> main);

		EasyBuilder& AddInput(engine::EventBuilder::BasicInputType);

		void buildEngine(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine,
						 int nCmdShow) const;
		void buildEngine(int argc, char* argv[]) const;
	private:
		void buildEngine(std::unique_ptr<IApplicationParameter> args) const;
	private:
		struct EasyBuilderPrivate *_members = nullptr;
	};
}
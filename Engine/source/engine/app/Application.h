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
		class Application: engine::constraints::NonCopyable
		{
		public:
			Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			~Application()  override;

			void update();
			void render();

			bool isActive() const;

			void stop();
			void start();

			const IApplicationParameter *getArguments() const;
		private:
			struct ApplicationPrivate *_members = nullptr;
		};
	}
}

#pragma once

#include "engine/constraints/NonCopyable.h"


namespace engine
{
	namespace app
	{
		/**
		* Base class for core logic of an application
		*/
		class IMain: constraints::NonCopyable
		{
		protected:
			/**Simple constructor only for child classes.*/
			IMain() = default;
		public:
			/**Simple destructor*/
			~IMain() override {};
			/**Called once when the application is started*/
			virtual void load() = 0;
			/**Called once per each frame to update the main*/
			virtual void update() = 0;
			/**Called once per each frame to render*/
			virtual void render() = 0;
		};
	}
}

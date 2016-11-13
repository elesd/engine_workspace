#pragma once

#include "engine/constraints/NonCopyable.h"


namespace engine
{
	namespace app
	{
		class IMain: constraints::NonCopyable
		{
		protected:
			IMain() = default;
		public:
			~IMain() override {};
			virtual void load() = 0;
			virtual void update() = 0;
			virtual void render() = 0;
		};
	}
}

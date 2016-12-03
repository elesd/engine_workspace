#pragma once

#include "engine/constraints/NonCopyable.h"

namespace engine
{
	namespace test
	{
		class BaseRegression;

		class TestManager : engine::NonCopyable
		{
		public:
			TestManager();
			TestManager(TestManager &&);
			~TestManager();

			TestManager &operator=(TestManager &&);

			void addRegression(BaseRegression &&regression);
			void setOutput(std::ostream &os);

			void run();
		private:
			struct TestManagerPrivate *_members = nullptr;
		};
	}
}
#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	namespace test
	{
		class BaseRegression;

		/**
		* The porpse of this class to manage test cases and regressions.
		*/
		class TestManager 
			: private engine::NonCopyable
		{
		public:
			/**Default constructable*/
			TestManager();
			/**Moveable, but not copyable*/
			TestManager(TestManager &&);
			/**PIMPL*/
			~TestManager();

			/**Moveable but not copyable*/
			TestManager &operator=(TestManager &&);

			/**
			* Add a regression for test.
			*/
			void addRegression(BaseRegression &&);

			/**
			* Set the output stream for the test cases for be able to create logs in file.
			*/
			void setOutput(std::ostream &);

			/**
			* Run all the regressions.
			*/
			void run();
		private:
			/**PIMPL*/
			struct TestManagerPrivate *_members = nullptr;
		};
	}
}
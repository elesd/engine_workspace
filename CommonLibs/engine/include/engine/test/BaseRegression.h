#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	namespace test
	{
		class TestSuit;

		/**
		* Base class for regressions.
		* Regressions contain test suites and collects run results.
		*/
		class BaseRegression: engine::NonCopyable
		{
		public:
			/**
			* Create a regression with a given name.
			*/
			BaseRegression(const std::string &name);
			/**PIMPL*/
			~BaseRegression();
			/**Moveable but not copyable*/
			BaseRegression(BaseRegression &&);

			/**Set the stream for the output*/
			void setStream(std::ostream *);

			/**Run all the test cases*/
			void run() const;

			/**@return Returns the number of test cases*/
			uint32_t getNumOfExecutedTC() const;

			/**@return Returns the number of Not ok test cases*/
			uint32_t getNumOfNokTC() const;

			/**@return Returns the name of the regression*/
			const std::string &getName() const;
		protected:
			/**Add a test suit to the regression.*/
			void addTestSuit(std::unique_ptr<TestSuit> &&);
		private:
			/**PIMPL*/
			struct BaseRegressionPrivate *_members = nullptr;
		};
	}
}

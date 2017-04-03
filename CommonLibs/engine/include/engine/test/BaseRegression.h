#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	namespace test
	{
		class TestSuite;

		class BaseRegression: engine::NonCopyable
		{
		public:
			BaseRegression(const std::string &name);
			~BaseRegression();
			BaseRegression(BaseRegression &&o);

			void setStream(std::ostream *os);

			void run() const;

			uint32_t getNumOfExecutedTC() const;

			uint32_t getNumOfNokTC() const;

			const std::string &getName() const;
		protected:
			void addTestSuite(std::unique_ptr<TestSuite> &&testSuite);
		private:
			struct BaseRegressionPrivate *_members = nullptr;
		};
	}
}

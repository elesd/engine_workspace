#pragma once

#include "engine/app/IApplicationParameter.h"

namespace engine
{
	namespace app
	{
		class StandardApplicationParameter: public IApplicationParameter
		{
		public:
			StandardApplicationParameter(uint32_t nParams, char *parameters[]);
		protected:
			StandardApplicationParameter();
		public:
			~StandardApplicationParameter()  override;
			const std::vector<std::string> &getParameters() const;
			const std::string &getBinaryName() const;
		protected:
			void init(uint32_t nParams, const std::vector<std::string> &parameters);
		private:
			struct StandardApplicationParameterPrivate *_members = nullptr;
		};
	}
}

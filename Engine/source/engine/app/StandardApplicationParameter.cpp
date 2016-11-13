#include "stdafx.h"

#include "engine/app/StandardApplicationParameter.h"

namespace engine
{
	namespace app
	{
		struct StandardApplicationParameterPrivate
		{
			std::vector<std::string> params;
			std::string binaryName;
		};

		StandardApplicationParameter::StandardApplicationParameter(uint32_t nParams, char *parameters[])
			: _members(new StandardApplicationParameterPrivate())
		{
			_members->binaryName = parameters[0];

			_members->params.reserve(nParams);
			for(uint32_t i = 1; i < nParams; ++i)
			{
				_members->params.push_back(parameters[i]);
			}
		}

		StandardApplicationParameter::StandardApplicationParameter()
			: _members(new StandardApplicationParameterPrivate())
		{

		}

		StandardApplicationParameter::~StandardApplicationParameter()
		{
			delete _members;
		}

		const std::string &StandardApplicationParameter::getBinaryName() const
		{
			return _members->binaryName;
		}

		const std::vector<std::string> &StandardApplicationParameter::getParameters() const
		{
			return _members->params;
		}

		void StandardApplicationParameter::init(uint32_t nParams, const std::vector<std::string> &parameters)
		{
			_members->binaryName = parameters[0];
			_members->params = parameters;
		}
	}
}

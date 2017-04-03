#pragma once

#include <stdexcept>

namespace engine
{
	struct InitializationError : std::logic_error
	{
		explicit InitializationError(const std::string &error):
			std::logic_error(error)
		{}

		explicit InitializationError(const char *error) :
			std::logic_error(error)
		{}
	};

	struct WrongStateError : std::logic_error
	{
		explicit WrongStateError(const std::string &error) :
			std::logic_error(error)
		{}

		explicit WrongStateError(const char *error) :
			std::logic_error(error)
		{}
	};

	struct UnsupportedFeature : std::logic_error
	{
		explicit UnsupportedFeature(const std::string &error) :
			std::logic_error(error)
		{}

		explicit UnsupportedFeature(const char *error) :
			std::logic_error(error)
		{}
	};
}
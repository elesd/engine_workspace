#pragma once

#include <stdexcept>

namespace engine
{
	struct ExpiredError : std::runtime_error
	{
		explicit ExpiredError(const std::string &error):
			std::runtime_error(error)
		{}

		explicit ExpiredError(const char *error) :
			std::runtime_error(error)
		{}
	};

	struct ItemNotFound : std::runtime_error
	{
		explicit ItemNotFound(const std::string &error) :
			std::runtime_error(error)
		{}

		explicit ItemNotFound(const char *error) :
			std::runtime_error(error)
		{}
	};
}
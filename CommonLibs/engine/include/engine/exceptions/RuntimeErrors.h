#pragma once

#include <stdexcept>

namespace engine
{
	/**
	* Exception when an element somewhere should be there but somehow it is missing during runtime.
	*/
	struct ItemNotFound : std::runtime_error
	{
		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/		explicit ItemNotFound(const std::string &error) :
			std::runtime_error(error)
		{}

		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit ItemNotFound(const char *error) :
			std::runtime_error(error)
		{}
	};
}
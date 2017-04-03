#pragma once

#include <stdexcept>

namespace engine
{
	/**
	* Exception for initialization errors
	*/
	struct InitializationError : std::logic_error
	{
		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit InitializationError(const std::string &error):
			std::logic_error(error)
		{}

		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit InitializationError(const char *error) :
			std::logic_error(error)
		{}
	};

	/**
	* Exception for functionality activation in wrong logical state.
	*/
	struct WrongStateError : std::logic_error
	{
		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit WrongStateError(const std::string &error) :
			std::logic_error(error)
		{}

		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit WrongStateError(const char *error) :
			std::logic_error(error)
		{}
	};

	/**
	* Exception for unupported features.
	*/
	struct UnsupportedFeature : std::logic_error
	{
		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit UnsupportedFeature(const std::string &error) :
			std::logic_error(error)
		{}

		/**
		* Init exception with error message
		* @param error: Specific error message for the certain case.
		*/
		explicit UnsupportedFeature(const char *error) :
			std::logic_error(error)
		{}
	};
}
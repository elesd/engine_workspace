#pragma once

#include <stdexcept>

namespace engine
{
	/** Exception for initialization errors. */
	struct InitializationError : std::logic_error
	{
		/**
		Create an initialization error with the reason
		@param error: The reason of the error.
		*/
		explicit InitializationError(const std::string &error):
			std::logic_error(error)
		{}

		/**
		Create an initialization error with the reason
		@param error: The reason of the error.
		*/
		explicit InitializationError(const char *error) :
			std::logic_error(error)
		{}
	};

	/** Exception for case when an object function is called in a wrong state.*/
	struct WrongStateError : std::logic_error
	{
		/**
		Create a wrong state error with the reason
		@param error: The reason of the error.
		*/
		explicit WrongStateError(const std::string &error) :
			std::logic_error(error)
		{}

		/**
		Create a wrong state error with the reason
		@param error: The reason of the error.
		*/
		explicit WrongStateError(const char *error) :
			std::logic_error(error)
		{}
	};

	/** Exception for the case when the feature is not ready yet.*/
	struct UnsupportedFeature : std::logic_error
	{
		/**
		Create the exception.
		@param error: The reason of the error.
		*/
		explicit UnsupportedFeature(const std::string &error) :
			std::logic_error(error)
		{}

		/**
		Create the exception.
		@param error: The reason of the error.
		*/
		explicit UnsupportedFeature(const char *error) :
			std::logic_error(error)
		{}
	};
}
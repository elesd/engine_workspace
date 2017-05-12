#pragma once

#include <engine/app/Application.h>

namespace engine
{
	namespace sdl
	{
		/**
		* Sdl specific implementation of the Application class
		*/
		class ApplicationImpl : public Application
		{
		public:
			/**
			* @copydoc
			*/
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			/** @copydoc */
			~ApplicationImpl() override {};
		private:
			/**
			* Update loop for Sdl specialities, like event loop.
			*/
			void updateImpl() override;
		};
	}
}


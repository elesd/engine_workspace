#pragma once

#include <engine/app/Application.h>

namespace engine
{
	namespace glfw
	{
		/** Glfw specific application implementation.*/
		class ApplicationImpl : public Application
		{
		public:
			/** @copydoc Application::Application */
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			/**Ensure polimorphism.*/
			~ApplicationImpl() override {};
		private:
			/**Update glfw module.*/
			void updateImpl() override;
		};
	}
}


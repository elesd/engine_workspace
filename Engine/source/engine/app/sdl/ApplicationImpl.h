#pragma once

#include <engine/app/Application.h>

namespace engine
{
	namespace sdl
	{
		class ApplicationImpl : public Application
		{
		public:
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			~ApplicationImpl() override {};
		private:
			void updateImpl() override;
		};
	}
}


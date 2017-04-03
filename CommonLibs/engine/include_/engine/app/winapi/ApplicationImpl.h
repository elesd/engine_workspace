#pragma once

#include <engine/app/Application.h>

namespace engine
{
	class IApplicationParameter;
	class IMain;

	namespace winapi
	{
		class ApplicationImpl : public Application
		{
		public:
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			~ApplicationImpl() override;
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		private:
			void updateImpl() override;

		};
	}
}
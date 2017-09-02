#pragma once

#include <engine/app/Application.h>

namespace engine
{
	class IApplicationParameter;

	namespace winapi
	{
		/**
		* Winapi specific implementations
		*/
		class ApplicationImpl : public Application
		{
		public:
			/**
			* Construct an application
			* @param arguments: The argument wrapper
			* @param main: Main class
			*/
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<GameMain> main);
			/**
			* Handles application event like exit.
			* @param hWnd: winProc parameter
			* @param message: winProc parameter
			* @param wParam: winProc parameter
			* @param lParam: winProc parameter
			* @return Retunrs true when the event was handled.
			*/
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		private:
			/**
			* @copydoc
			*/
			void updateImpl() override;

		};
	}
}
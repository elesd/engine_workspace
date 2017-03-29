#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/IModuleExtension.h>


namespace engine
{
	class Context;
	namespace winapi
	{
		class WinProcExtension : public IModuleExtension,
			private NonCopyable,
			private NonMoveable
		{
		public:
			static const std::string ExtensionId;
		public:
			WinProcExtension(Context *context);
			~WinProcExtension() override;
			bool execute(HWND hWnd,
							UINT message,
							WPARAM wParam,
							LPARAM lParam);

		private:
			bool handleWindowEvents(HWND hWnd,
									UINT message,
									WPARAM wParam,
									LPARAM lParam);
			bool handleKeyboardEvents(HWND hWnd,
									  UINT message,
									  WPARAM wParam,
									  LPARAM lParam);
			bool handleMouseEvents(HWND hWnd,
								   UINT message,
								   WPARAM wParam,
								   LPARAM lParam);

			struct WinProcExtensionPrivate *_members = nullptr;
		};
	}
}
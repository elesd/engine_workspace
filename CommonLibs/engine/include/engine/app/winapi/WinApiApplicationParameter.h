#pragma once
#include "engine/app/StandardApplicationParameter.h"

#include <windows.h>

namespace engine
{
	namespace app
	{
		namespace winapi
		{
			/**
			* WinApi applications have special parameters. This class is the specialization of standard parameters.
			*/
			class WinApiApplicationParameter : public app::StandardApplicationParameter
			{
			public:
				/**
				* WinApi application parameter initialization.
				* @param instance: Handler for the current application instance.
				* @param prevInstance: Due to historical reason we got the previous application handler too.
				* @param cmdLine: Standard command line arguments except the current application name
				* @param cmdShow: flag for window showing.
				* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ff381406(v=vs.85).aspx
				*/
				WinApiApplicationParameter(HINSTANCE instance,
										   HINSTANCE prevInstance,
										   LPSTR cmdLine,
										   int cmdShow);

				/**Destructor for PIMPL*/
				~WinApiApplicationParameter() override;

				/**
				* @return Returns the handler for the application instance
				*/
				HINSTANCE getInstance() const;

				/**
				* @return Returns the flag for window showing parameter (minimalize/maximize/show normaly)
				*/
				int getCmdShow() const;
			private:
				/**PIMPL*/
				struct WinApiApplicationParameterPrivate *_members = nullptr;
			};
		}
	}
}

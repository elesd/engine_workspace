#include <stdafx.h>
#if ENGINE_USE_WINAPI

#include <engine/app/winapi/WinApiApplicationParameter.h>

/////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{
		struct WinApiApplicationParameterPrivate
		{
			HINSTANCE instance;
			HINSTANCE prevInstance;
			int cmdShow;
		};

		WinApiApplicationParameter::WinApiApplicationParameter(HINSTANCE instance,
															   HINSTANCE prevInstance,
															   LPSTR cmdLine,
															   int cmdShow)
															   :_members(new WinApiApplicationParameterPrivate())
		{
			int nArgs;
			LPWSTR *arguments = CommandLineToArgvW(GetCommandLineW(), &nArgs);
			std::vector<std::string> parameters;
			for(uint32_t i = 0; i < uint32_t(nArgs); ++i)
			{
				std::stringstream sstream;
				sstream << arguments[i];
				parameters.push_back(sstream.str());
			}
			StandardApplicationParameter::init(nArgs, parameters);

			_members->instance = instance;
			_members->prevInstance = prevInstance;
			_members->cmdShow = cmdShow;
		}

		WinApiApplicationParameter::~WinApiApplicationParameter()
		{
			delete _members;
		}

		HINSTANCE WinApiApplicationParameter::getInstance() const
		{
			return _members->instance;
		}

		int WinApiApplicationParameter::getCmdShow() const
		{
			return _members->cmdShow;
		}
	}
}

#else 

#include <engine/app/winapi/empty/WinApiApplicationParameter.cpp>

#endif
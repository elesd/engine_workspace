#pragma once

void LogToStream(std::ostringstream &os, const std::string &format);

template<class T, class ...Args>
void LogToStream(std::ostringstream &os, const std::string &format, T value, Args... args)
{
	size_t pos = format.find('%');
	if(pos != std::string::npos)
	{
		std::string firstPart = format.substr(0, pos);
		os << firstPart << value;
		if(pos + 1 < format.size())
		{
			std::string secondPart = format.substr(pos + 1);
			LogToStream(os, secondPart, args...);
		}
		else
		{
			os << std::endl;
		}
	}
}
#if TUTORIAL_USE_WINAPI
template<class ...Args>
void Log(const std::string &format, Args... params)
{
	std::ostringstream os;
	LogToStream(os, format, params...);
	std::string str = os.str();
	OutputDebugString(str.c_str());
}
#else
template<class ...Args>
void Log(const std::string &format, Args... params)
{
	std::ostringstream os;
	LogToStream(os, format, params...);
	std::string str = os.str();
    std::cout << str << std::endl;
}

#endif

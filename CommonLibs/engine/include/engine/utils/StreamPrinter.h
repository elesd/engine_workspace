#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class StreamPrinter
		: private NonCopyable
		, private NonMoveable
	{
	public:
		StreamPrinter(std::ostream&);
		~StreamPrinter();

		void print(const std::string &format);

		template<typename T, class ...Args>
		void print(const std::string &format, T value, Args... args);
	private:
		std::ostream& getOutput();
	private:
		struct StreamPrinterPrivate* _members = nullptr;
	};


	template<class T, class ...Args>
	void StreamPrinter::print(const std::string& format, T value, Args... params)
	{
		size_t pos = format.find('%');
		if(pos != std::string::npos)
		{
			std::string firstPart = format.substr(0, pos);
			getOutput() << firstPart << value;
			if(pos + 1 < format.size())
			{
				std::string secondPart = format.substr(pos + 1);
				print(secondPart, params...);
			}
			else
			{
				getOutput() << std::endl;
			}
		}
		else
		{
			FAIL("wrong format at console print out");
		}
	}
}
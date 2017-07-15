#pragma once

#include <engine/utils/StreamPrinter.h>

namespace engine
{
	class Console
	{
	public:
		Console() = default;
		virtual ~Console() {};

		template<typename... T>
		void print(const std::string& format, T... params);

	private:
		virtual void printImpl(const std::string&) const;
	};

	template<typename... T>
	void Console::print(const std::string& format, T... params)
	{
		std::ostringstream os;
		StreamPrinter printer(os);
		printer.print(format, params...);
		std::string str = os.str();
		printImpl(str);
	}

}
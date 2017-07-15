#include <stdafx.h>
#include <engine/utils/StreamPrinter.h>

namespace engine
{
	struct StreamPrinterPrivate
	{
		std::ostream& os;
		explicit StreamPrinterPrivate(std::ostream& os) 
			: os(os)
		{ }
	};
	StreamPrinter::StreamPrinter(std::ostream& os)
		: _members(new StreamPrinterPrivate(os))
	{

	}

	StreamPrinter::~StreamPrinter()
	{
		delete _members;
		_members = nullptr;
	}

	std::ostream& StreamPrinter::getOutput()
	{
		return _members->os;
	}

	void StreamPrinter::print(const std::string &format)
	{
		_members->os << format << std::endl;
	}

}
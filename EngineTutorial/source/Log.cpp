#include <stdafx.h>
#include <Log.h>
///////////////////////////////////////////////////////////////////////////////

void LogToStream(std::ostringstream &os, const std::string &format)
{
	os << format << std::endl;
}

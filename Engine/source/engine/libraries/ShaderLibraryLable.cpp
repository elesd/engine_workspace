#include <stdafx.h>
#include <engine/libraries/ShaderLibraryLable.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{

	ShaderLibraryLabel::ShaderLibraryLabel(const std::string& name, const FilePath& path, ShaderType type, const std::string& mainFunction)
		: name(name)
		, path(path)
		, type(type)
		, mainFunction(mainFunction)
	{

	}
}
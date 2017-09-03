#pragma once

#include <engine/fileSystem/FilePath.h>

namespace engine
{
	class FilePath;
	class Shader;

	enum class ShaderType;

	struct ShaderLibraryLabel
	{
		ShaderLibraryLabel() = default;
		ShaderLibraryLabel(const std::string& name, const FilePath& path, ShaderType type, const std::string& mainFunction);

		std::string name;
		FilePath path;
		ShaderType type;
		std::string mainFunction;
	};
}
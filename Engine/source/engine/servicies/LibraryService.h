#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class ShaderInstance;
	class ShaderLibrary;

	struct ShaderLibraryLabel;

	enum class ShaderType;

	class LibraryService final
		: private NonCopyable
		, private NonMoveable
	{
		friend class Application;
	private:
		explicit LibraryService(ShaderLibrary* shaderLibrary);
	public:
		~LibraryService();

		std::unique_ptr<ShaderInstance> getShader(ShaderType type, const std::string& shaderName);
		void addShader(const ShaderLibraryLabel& label);
		bool hasShader(ShaderType type, const std::string& shaderName);
	private:
		struct LibraryServicePrivate* _members = nullptr;
	};
}
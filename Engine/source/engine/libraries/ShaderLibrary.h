#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/libraries/ShaderLibraryLable.h>

namespace engine
{
	class Shader;
	class ShaderInstance;

	enum class ShaderType;

	struct ShaderLibraryEntry;

	class ShaderLibrary final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		ShaderLibrary();
		~ShaderLibrary();

		void addShader(const ShaderLibraryLabel& label);
		std::unique_ptr<ShaderInstance> getShader(ShaderType type, const std::string& name) const;
		bool hasShader(ShaderType type, const std::string& name) const;

		void update();
	private:
		std::shared_ptr<Shader> findShader(ShaderType type, const std::string& name) const;
		void removeShader(Shader* shader);
		void loadShader(const ShaderLibraryLabel& label);
	private:
		struct ShaderLibraryPrivate* _members = nullptr;
	};
}
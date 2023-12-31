#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/constraints/Lockable.h>

namespace engine
{
	class FilePath;

	enum class ShaderType
	{
		VertexShader,
		FragmentShader
	};
	struct ShaderTypeHelper
	{
		static const std::vector<ShaderType>& getAll();
	};

	class ShaderCompilationData;

	class Shader
		: private NonCopyable
		, private NonMoveable
		, public Lockable<Shader>
	{
	public:
		Shader(ShaderType);
		virtual ~Shader();

		bool init(const FilePath& filePath, const std::string& mainFunctionName);
		void init(const std::string& shaderCode, const std::string& mainFunctionName);

		bool isInitialized() const;
		bool isCompiled(const std::string& technique) const;
		bool isSame(const std::string& technique, const Shader& o) const;
		const std::string& getCode() const;
		ShaderType getShaderType() const;
		const std::string& getMainFunctionName();
		void setCompiled(const std::string& techniqueName, std::unique_ptr<ShaderCompilationData>&& compilationData);
		const ShaderCompilationData* getCompilationData(const std::string& techniqueName) const;
		void releaseCompilationData(const std::string& technique);

	private:
		struct ShaderPrivate* _members = nullptr;
	};
}

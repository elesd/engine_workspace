#pragma once

namespace engine
{
	class Shader;
	class ShaderCompileOptions;


	enum class ShaderVersion;

	class MaterialDescription
	{
	public:
		MaterialDescription();
		~MaterialDescription();
		MaterialDescription(const MaterialDescription&);
		MaterialDescription(MaterialDescription&&);

		MaterialDescription& operator=(const MaterialDescription&);
		MaterialDescription& operator=(MaterialDescription&&);

		void setShaderVersion(ShaderVersion);
		void addTechnique(const std::string& name, const ShaderCompileOptions& compileOptions);
		void setVertexShader(Shader* vertexShader);
		void setFragmentShader(Shader* fragmentShader);

		ShaderVersion getShaderVersion() const;
		Shader* getVertexShader() const;
		Shader* getFragmentShader() const;
		ShaderCompileOptions getOption(const std::string& techniqueName) const;
		const std::map<std::string, ShaderCompileOptions>& getTechniqueMap() const;
	private:
		struct MaterialDescriptionPrivate* _members = nullptr;
		
	};
}
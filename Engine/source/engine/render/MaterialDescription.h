#pragma once

namespace engine
{
	class Shader;
	class ShaderCompileOptions;


	enum class ShaderVersion;

	class MaterialDescription
	{
	public:
		explicit MaterialDescription(ShaderVersion);
		~MaterialDescription();
		MaterialDescription(const MaterialDescription&);
		MaterialDescription(MaterialDescription&&);

		MaterialDescription& operator=(const MaterialDescription&);
		MaterialDescription& operator=(MaterialDescription&&);

		void setDefaultTechnique(const ShaderCompileOptions& compileOptions);
		void addTechnique(const std::string& name, const ShaderCompileOptions& compileOptions);
		void setVertexShader(Shader* vertexShader);
		void setFragmentShader(Shader* fragmentShader);

		ShaderCompileOptions createEmptyOptions() const;

		ShaderVersion getShaderVersion() const;
		Shader* getVertexShader() const;
		Shader* getFragmentShader() const;
		const ShaderCompileOptions& getOptions(const std::string& techniqueName) const;
		const std::map<std::string, ShaderCompileOptions>& getTechniqueMap() const;
	private:
		struct MaterialDescriptionPrivate* _members = nullptr;
		
	};
}
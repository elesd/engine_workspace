#pragma once

namespace engine
{
	class FilePath;
	class Shader
	{
	public:
		Shader();
		~Shader();

		bool init(const FilePath& filePath);
		void init(const std::string& shaderCode);

		bool isInitialized() const;

		const std::string& getCode() const;
		const std::vector<std::string>& getDefines() const;
		void addShaderDefine(const std::string& define);
		bool removeShaderDefine(const std::string& define);
		bool hasShaderDefine(const std::string &define) const;
	private:
		struct ShaderPrivate* _members = nullptr;
	};
}

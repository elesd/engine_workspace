#pragma once


namespace engine
{
	class Driver;
	class Shader;
	class ShaderCompileOptions;

	enum class ShaderVersion;

	class ShaderCompiler
	{
		friend class RenderContext;
	private:
		ShaderCompiler(Driver* driver, ShaderVersion version);
	public:
		ShaderCompiler(const ShaderCompiler&);
		ShaderCompiler(ShaderCompiler&&);
		~ShaderCompiler();

		ShaderCompiler& operator=(const ShaderCompiler&);
		ShaderCompiler& operator=(ShaderCompiler&&);


		void init(const std::map<std::string, ShaderCompileOptions>& techniqueMap);

		bool compileShader(Shader* shader, const std::string& techniqueName);
		const ShaderCompileOptions& getOptions(const std::string& techniqueName) const;
		ShaderCompileOptions& getOptions(const std::string& techniqueName);

	private:
		struct ShaderCompilerPrivate* _members = nullptr;
	};
}
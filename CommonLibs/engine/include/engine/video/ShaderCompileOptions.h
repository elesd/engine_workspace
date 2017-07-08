#pragma once

namespace engine
{
	class AttributeFormat;

	enum class ShaderVersion
	{
		HLSL_4_0_level_9_1,
		HLSL_4_0_level_9_3,
		HLSL_4_0,
		HLSL_4_1,
		HLSL_5_0,
		Num
	};

	enum class ShaderCompileFlag
	{
		None,
		Debug,
		SkipOptimization,
		PackMatrixRowMajor,
		PackMatrixColumnMajor,
		WarningAreErrors
	};

	class ShaderCompileOptions final
	{
	public:
		ShaderCompileOptions();
		ShaderCompileOptions(ShaderVersion);
		ShaderCompileOptions(const ShaderCompileOptions&);
		ShaderCompileOptions(ShaderCompileOptions&&);

		~ShaderCompileOptions();

		ShaderCompileOptions& operator=(const ShaderCompileOptions&);
		ShaderCompileOptions& operator=(ShaderCompileOptions&&);

		bool operator==(const ShaderCompileOptions&) const;

		ShaderVersion getVersion() const;

		void addDefine(const std::string& define);
		bool hasDefine(const std::string& define) const;
		void removeDefine(const std::string& define);
		const std::vector<std::string>& getDefines() const;

		void addFlag(ShaderCompileFlag);
		bool hasFlag(ShaderCompileFlag flag) const;
		void removeFlag(ShaderCompileFlag);
		const std::vector<ShaderCompileFlag>& getFlags() const;
		
	private:
		struct ShaderCompileOptionsPrivate* _members = nullptr;
		
	};
}
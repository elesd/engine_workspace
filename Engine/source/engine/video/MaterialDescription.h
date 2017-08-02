#pragma once

namespace engine
{
	class AttributeFormat;
	class Shader;
	class ShaderCompileOptions;

	class ShaderResourceDescription;
	class EffectDescription;
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

		EffectDescription createEffectDescription(const std::string& name) const;
		void setDefaultEffect(const EffectDescription& description);
		void addEffect(const EffectDescription& description);

		void setAttributeFormat(const AttributeFormat& attributeFormat);
		void setVertexShader(Shader* vertexShader);
		void setFragmentShader(Shader* fragmentShader);
		void addParameter(const ShaderResourceDescription &description);

		const std::vector<ShaderResourceDescription>& getParameters() const;
		const AttributeFormat& getAttributeFormat() const;
		ShaderVersion getShaderVersion() const;
		Shader* getVertexShader() const;
		Shader* getFragmentShader() const;
		const EffectDescription& getEffectDescription(const std::string& techniqueName) const;
		const std::map<std::string, EffectDescription>& getEffectMap() const;
	private:
		struct MaterialDescriptionPrivate* _members = nullptr;
		
	};
}
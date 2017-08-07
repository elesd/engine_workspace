#pragma once

namespace engine
{
	class ShaderCompileOptions;
	class ShaderResourceDescription;

	class EffectDescription
	{
	public:
		EffectDescription(const std::string& name, const ShaderCompileOptions& options);
		~EffectDescription();
		EffectDescription(const EffectDescription& o);
		EffectDescription(EffectDescription&& o);

		EffectDescription& operator=(const EffectDescription&);
		EffectDescription& operator=(EffectDescription&&);

		void addParameter(const ShaderResourceDescription &description);

		const std::vector<ShaderResourceDescription>& getParameters() const;
		const std::string& getName() const;
		const ShaderCompileOptions& getOptions() const;
		ShaderCompileOptions& getOptions();
	private:
		struct EffectDescriptionPrivate* _members = nullptr;
	};
}
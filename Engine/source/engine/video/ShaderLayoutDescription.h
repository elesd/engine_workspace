#pragma once

namespace engine
{
	enum class GPUMemberType;

	struct ShaderLayout
	{
		GPUMemberType type;
		std::string name;
		bool operator==(const ShaderLayout& o) const;
	};

	class ShaderLayoutDescription
	{
	public:
		ShaderLayoutDescription();
		ShaderLayoutDescription(const ShaderLayoutDescription&);
		ShaderLayoutDescription(ShaderLayoutDescription&&);
		~ShaderLayoutDescription();

		ShaderLayoutDescription& operator=(const ShaderLayoutDescription&);
		ShaderLayoutDescription& operator=(ShaderLayoutDescription&&);

		bool operator==(const ShaderLayoutDescription&) const;
		void insertAttribute(GPUMemberType type, uint32_t layout, const std::string& name);
		size_t getNumOfAttributes() const;
		void removeAttirbute(uint32_t layout);
		const ShaderLayout& getAttribute(uint32_t layout) const;
	private:
		struct ShaderLayoutDescriptionPrivate* _members = nullptr;
	};
}
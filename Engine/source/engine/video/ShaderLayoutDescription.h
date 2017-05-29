#pragma once

namespace engine
{
	enum class ShaderMemberType
	{
		Undef,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	struct ShaderLayout
	{
		ShaderMemberType type;
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
		void insertAttribute(ShaderMemberType type, uint32_t layout, const std::string& name);
		size_t getNumOfAttributes() const;
		void removeAttirbute(uint32_t layout);
		ShaderLayout getAttribute(uint32_t layout) const;
	private:
		struct ShaderLayoutDescriptionPrivate* _members = nullptr;
	};
}
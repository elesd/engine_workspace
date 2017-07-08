#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Effect;
	

	class EffectComperator
		: private NonCopyable
		, private NonMoveable
	{
	public:
		enum class DifferenceType
		{
			VertexShader,
			FragmentShader,
			Num
		};
	public:
		explicit EffectComperator();
		~EffectComperator();

		void compare(const Effect* a, const Effect* b);
		bool isChanged(DifferenceType type) const;
		bool hasAnyChange() const;
	private:
		struct EffectComperatorPrivate* _members = nullptr;
	};
}
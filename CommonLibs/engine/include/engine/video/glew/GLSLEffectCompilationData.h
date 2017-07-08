#pragma once

#include <engine/video/EffectCompilationData.h>

namespace engine
{
	namespace glew
	{
		class GLSLEffectCompilationData : public EffectCompilationData
		{
		public:
			GLSLEffectCompilationData();
			~GLSLEffectCompilationData() override;

			void setOk(GLuint programID);
			GLuint getProgramId() const;
		private:
			struct GLSLEffectCompilationDataPrivate* _members = nullptr;
		};
	}
}
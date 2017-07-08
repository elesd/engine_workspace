#pragma once

#include <engine/video/ShaderCompilationData.h>

namespace engine
{
	class ShaderCompileOptions;

	namespace glew
	{
		class GLSLVSCompilationData
			: public ShaderCompilationData
		{
		public:
			GLSLVSCompilationData(const ShaderCompileOptions& options);
			~GLSLVSCompilationData() override;
			void setOk(GLuint shaderId);
			GLuint getShaderId() const;

		private:
			void releaseImpl() override;

		private:
			struct GLSLVSCompilationDataPrivate* _members = nullptr;
		};
	}
}
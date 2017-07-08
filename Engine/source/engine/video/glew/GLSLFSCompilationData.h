#pragma once

#include <engine/video/ShaderCompilationData.h>

namespace engine
{
	class ShaderCompileOptions;

	namespace glew
	{
		class GLSLFSCompilationData
			: public ShaderCompilationData
		{
		public:
			GLSLFSCompilationData(const ShaderCompileOptions& options);
			~GLSLFSCompilationData() override;
			
			void setOk(GLuint shaderId);
			GLuint getShaderId() const;
		private:
			void releaseImpl() override;
		private:
			struct GLSLFSCompilationDataPrivate* _members = nullptr;
		};
	}
}
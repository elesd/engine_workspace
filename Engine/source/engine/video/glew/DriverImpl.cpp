#include <stdafx.h>
#include <engine/video/glew/DriverImpl.h>

#include <engine/video/Effect.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/Material.h>
#include <engine/video/RenderTarget.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/AttributeFormat.h>
#include <engine/video/VertexBuffer.h>

#include <engine/video/glew/GLSLEffectCompilationData.h>
#include <engine/video/glew/GLSLVSCompilationData.h>
#include <engine/video/glew/GLSLFSCompilationData.h>
#include <engine/video/glew/IndexBufferObject.h>
#include <engine/video/glew/MaterialContextImpl.h>
#include <engine/video/glew/VertexBufferObject.h>

#include <engine/video/GPUTypes.h>

namespace
{
	std::pair<bool, std::string> compileGLSLShader(GLuint shaderId)
	{
		glCompileShader(shaderId);

		bool ok = true;
		std::string errorStr = "";
		GLint isCompiled = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorData(maxLength);
			glGetShaderInfoLog(shaderId, maxLength, &maxLength, errorData.data());
			glDeleteShader(shaderId);

			errorStr = errorData.data();
			ok = false;
		}
		return std::make_pair(ok, errorStr);
	}

	size_t getTypeSize(engine::GPUMemberType type)
	{
		switch(type)
		{
			case engine::GPUMemberType::Float: return 4; break;
			case engine::GPUMemberType::Vec2: return 8; break;
			case engine::GPUMemberType::Vec3: return 12; break;
			case engine::GPUMemberType::Vec4: return 16; break;
			case engine::GPUMemberType::Mat3: return 36; break;
			case engine::GPUMemberType::Mat4: return 64; break;
			case engine::GPUMemberType::Undef:
			default: FAIL("Unknown gpu member type"); return 0;
			break;
		}
	}

	size_t getAttirbuteMemberCount(engine::GPUMemberType type)
	{
		switch(type)
		{
			case engine::GPUMemberType::Float: return 1; break;
			case engine::GPUMemberType::Vec2: return 2; break;
			case engine::GPUMemberType::Vec3: return 3; break;
			case engine::GPUMemberType::Vec4: return 4; break;
			case engine::GPUMemberType::Mat3: return 9; break;
			case engine::GPUMemberType::Mat4: return 16; break;
			case engine::GPUMemberType::Undef:
			default: FAIL("Unknown gpu member type"); return 0;
			break;
		}
	}

}

namespace engine
{
	namespace glew
	{
		GLuint DriverImpl::createBuffer()
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);
			return buffer;
		}

		void DriverImpl::drawImpl(const VertexBuffer* verticies, const IndexBufferBase* indicies) 
		{
			ASSERT(verticies->isMapped());
			ASSERT(indicies->isMapped());

			// TODO Add Buffer Array implementation
			verticies->getBufferObject()->bind();
			indicies->getBufferObject()->bind();

			GLenum mode = 0;
			switch(indicies->getPrimitiveType())
			{
				case PrimitiveType::Triangle: mode = GL_TRIANGLES; break;
				default: FAIL("Unknown primitive type"); mode = GL_TRIANGLES; break;
			}

			GLsizei type = GL_UNSIGNED_INT;
			size_t stride = indicies->getStride();
			switch(stride)
			{
				case 2: type = GL_UNSIGNED_SHORT; break;
				case 4: type = GL_UNSIGNED_INT; break;
				default: FAIL("Type deduction is faild based on stride."); type = GL_UNSIGNED_INT; break;
			}

			glDrawElements(
				mode,
				indicies->count(),    // count
				type,   // type
				(void*)0           // element array buffer offset
			);

			indicies->getBufferObject()->unbind();
			verticies->getBufferObject()->unbind();
		}

		void DriverImpl::setRenderTargetImpl(RenderTarget* renderTarget)
		{
			HARD_FAIL("Unimplemented");
		}

		void DriverImpl::resetRenderTargetImpl()
		{
			HARD_FAIL("Unimplemented");
		}

		void DriverImpl::setMaterialContextImpl(const MaterialContext* materialContext)
		{
			const MaterialContextImpl* glslMaterialContext = static_cast<const MaterialContextImpl*>(materialContext);
			glBindVertexArray(glslMaterialContext->getVAO());
		}

		void DriverImpl::compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options)
		{
			GLenum shaderType = 0;
			switch(shader->getShaderType())
			{
				case ShaderType::VertexShader: shaderType = GL_VERTEX_SHADER; break;
				case ShaderType::FragmentShader: shaderType = GL_FRAGMENT_SHADER; break;
				default: HARD_FAIL("Unknown shader type at compilation"); break;
			}
			GLuint shaderId = glCreateShader(shaderType);
			const std::string& shaderCode = shader->getCode();
			const char* shaderCodePtr = shaderCode.c_str();
			glShaderSource(shaderId, 1, &shaderCodePtr, 0);

			bool ok = false;
			std::string errorStr;

			std::tie(ok, errorStr) = compileGLSLShader(shaderId);

			std::unique_ptr<ShaderCompilationData> compilationData;
			switch(shader->getShaderType())
			{
				case ShaderType::VertexShader: 
				{
					compilationData.reset(new GLSLVSCompilationData(options));
					GLSLVSCompilationData *glslData = static_cast<GLSLVSCompilationData*>(compilationData.get());
					if(ok)
					{
						glslData->setOk(shaderId);
					}
					else
					{
						glslData->setError(errorStr);
					}
				}
				break;
				case ShaderType::FragmentShader: 
				{
					compilationData.reset(new GLSLFSCompilationData(options));
					GLSLFSCompilationData *glslData = static_cast<GLSLFSCompilationData*>(compilationData.get());
					if(ok)
					{
						glslData->setOk(shaderId);
					}
					else
					{
						glslData->setError(errorStr);
					}
				}
				break;
				default: HARD_FAIL("Unknown shader type at compilation"); break;
			}
			shader->setCompiled(techniqueName, std::move(compilationData));
		}

		void DriverImpl::compileEffectImpl(Effect* effect) 
		{
			GLuint programID = glCreateProgram();
			const GLSLFSCompilationData* compilationDataFS = static_cast<const GLSLFSCompilationData*>(effect->getFragmentShaderData());
			const GLSLVSCompilationData* compilationDataVS = static_cast<const GLSLVSCompilationData*>(effect->getVertexShaderData());
			glAttachShader(programID, compilationDataVS->getShaderId());
			glAttachShader(programID, compilationDataFS->getShaderId());
			glLinkProgram(programID);

			// Check the program
			GLint result = GL_FALSE;
			int32_t infoLogLength = 0;
			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::unique_ptr<GLSLEffectCompilationData> compilationResult = std::make_unique<GLSLEffectCompilationData>();
			if(result == GL_TRUE)
			{
				compilationResult->setOk(programID);
			}
			else
			{
				if(infoLogLength > 0)
				{
					std::vector<char> errorData(infoLogLength + 1);
					glGetProgramInfoLog(programID, infoLogLength, NULL, errorData.data());
					compilationResult->setError(errorData.data());
				}
				else
				{
					compilationResult->setError("Unknown error");
				}
			}


			glDetachShader(programID, compilationDataVS->getShaderId());
			glDetachShader(programID, compilationDataFS->getShaderId());

			effect->getFragmentShader()->releaseCompilationData(effect->getName());
			effect->getVertexShader()->releaseCompilationData(effect->getName());
			effect->setCompiled(std::move(compilationResult));
		}

		void DriverImpl::setEffectImpl(Effect* effect)
		{
			const GLSLEffectCompilationData* compilationData = static_cast<const GLSLEffectCompilationData*>(effect->getCompilationData());
			glUseProgram(compilationData->getProgramId());
		}

		void DriverImpl::setShaderImpl(Shader* shader, const std::string& techniqueName)
		{
			UNSUPPORTED_ERROR();
		}

		std::unique_ptr<RenderTarget> DriverImpl::createRenderTargetImpl(std::unique_ptr<Texture>&& texture)
		{
			return std::unique_ptr<RenderTarget>(new RenderTarget(std::move(texture)));
		}

		std::unique_ptr<MaterialContext> DriverImpl::createMaterialContextImpl(const Material* material)
		{
			GLuint vao = 0;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			const AttributeFormat& layoutDesc = material->getAttributeFormat();
			size_t layoutSize = 0;
			for(size_t i = 0; i < layoutDesc.getNumOfAttributes(); ++i)
			{
				layoutSize += getTypeSize(layoutDesc.getAttribute(i).type);
			}

			size_t offset = 0;
			for(size_t i = 0; i < layoutDesc.getNumOfAttributes(); ++i)
			{
				glEnableVertexAttribArray(i);
				ShaderLayout layout = layoutDesc.getAttribute(i);
				glVertexAttribPointer(
					i,
					getAttirbuteMemberCount(layout.type),
					GL_FLOAT, // TODO
					false, // TODO
					layoutSize,
					(void*)offset
				);
				offset += getTypeSize(layout.type);
			}
			glBindVertexArray(0);

			return std::make_unique<MaterialContextImpl>(material, vao);
		}



	
	}
}
#include <stdafx.h>
#include <engine/video/glew/DriverImpl.h>

#include <engine/video/BufferContext.h>
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


}

namespace engine
{
	namespace glew
	{
		DriverImpl::DriverImpl()
		{
			checkErrors();
		}

		void DriverImpl::checkErrors()
		{
#if ENGINE_OPENGL_PARANOID
			GLenum err = GL_NO_ERROR;
			while((err = glGetError()) != GL_NO_ERROR)
			{
				std::cerr << "ERROR " << err << std::endl;
			}
#endif
		}

		void DriverImpl::printBindings()
		{
			GLint currentVAO = 0;
			GLint currentVBO = 0;
			GLint currentIndexBuffer = 0;
			GLint currentProgram = 0;
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
			glGetIntegerv(GL_INDEX_ARRAY_BUFFER_BINDING, &currentIndexBuffer);
			glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
			std::cout << "VAO: " << currentVAO << std::endl;
			std::cout << "VBO: " << currentVBO << std::endl;
			std::cout << "IndexBuffer: " << currentIndexBuffer << std::endl;
			std::cout << "Program: " << currentProgram << std::endl;
		}

		void DriverImpl::drawImpl(BufferContext* bufferContext)
		{
			if(bufferContext->allBuffersBound() == false)
			{
				bufferContext->bindBuffers();
			}

			GLenum mode = 0;
			switch(bufferContext->getIndexBuffer()->getPrimitiveType())
			{
				case PrimitiveType::Triangle: mode = GL_TRIANGLES; break;
				default: FAIL("Unknown primitive type"); mode = GL_TRIANGLES; break;
			}

			GLsizei type = GL_UNSIGNED_INT;
			size_t stride = bufferContext->getIndexBuffer()->getStride();
			switch(stride)
			{
				case 2: type = GL_UNSIGNED_SHORT; break;
				case 4: type = GL_UNSIGNED_INT; break;
				default: FAIL("Type deduction is faild based on stride."); type = GL_UNSIGNED_INT; break;
			}

			glDrawElements(
				mode,
				bufferContext->getIndexBuffer()->count(),    // count
				type,   // type
				(void*)0           // element array buffer offset
			);
			checkErrors();
			bufferContext->unbindBuffers();
		}

		void DriverImpl::setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) 
		{
			glViewport(x, y, width, height);
			checkErrors();
		}


		void DriverImpl::setRenderTargetImpl(RenderTarget* renderTarget)
		{
			HARD_FAIL("Unimplemented");
		}

		void DriverImpl::resetRenderTargetImpl()
		{
			HARD_FAIL("Unimplemented");
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
			checkErrors();
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
			checkErrors();
			glAttachShader(programID, compilationDataFS->getShaderId());
			checkErrors();
			glLinkProgram(programID);
			checkErrors();

			// Check the program
			GLint result = GL_FALSE;
			int32_t infoLogLength = 0;
			glGetProgramiv(programID, GL_LINK_STATUS, &result);
			checkErrors();
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			checkErrors();
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
					checkErrors();
					compilationResult->setError(errorData.data());
				}
				else
				{
					compilationResult->setError("Unknown error");
				}
			}


			glDetachShader(programID, compilationDataVS->getShaderId());
			checkErrors();
			glDetachShader(programID, compilationDataFS->getShaderId());
			checkErrors();

			effect->getFragmentShader()->releaseCompilationData(effect->getName());
			effect->getVertexShader()->releaseCompilationData(effect->getName());
			effect->setCompiled(std::move(compilationResult));
		}

		void DriverImpl::setEffectImpl(Effect* effect)
		{
			const GLSLEffectCompilationData* compilationData = static_cast<const GLSLEffectCompilationData*>(effect->getCompilationData());
			// TODO check calling it in each frame
			glUseProgram(compilationData->getProgramId());
			checkErrors();
		}

		void DriverImpl::setShaderImpl(Shader* shader, const std::string& techniqueName)
		{
			UNSUPPORTED_ERROR();
		}

		std::unique_ptr<RenderTarget> DriverImpl::createRenderTargetImpl(std::unique_ptr<Texture>&& texture)
		{
			return std::unique_ptr<RenderTarget>(new RenderTarget(std::move(texture)));
		}

		//std::unique_ptr<MaterialContext> DriverImpl::createMaterialContextImpl(const Material* material)
		//{
		//	GLuint vao = 0;
		//	glGenVertexArrays(1, &vao);
		//	checkErrors();
		//	glBindVertexArray(vao);
		//	checkErrors();
		//	const AttributeFormat& layoutDesc = material->getAttributeFormat();
		//	size_t layoutSize = 0;
		//	for(size_t i = 0; i < layoutDesc.getNumOfAttributes(); ++i)
		//	{
		//		layoutSize += getTypeSize(layoutDesc.getAttribute(i).type);
		//	}
		//	std::vector<float> data(
		//	{
		//		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		//		1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		//		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		//	});
		//	std::vector<char> tempData(data.size() * sizeof(float), 0);
		//	memcpy(tempData.data(), data.data(), data.size());
		//	VertexBufferObject tempVBO(layoutSize, this);
		//	tempVBO.bind();
		//	tempVBO.setData(tempData.data(), layoutSize);
		//	size_t offset = 0;
		//	for(size_t i = 0; i < layoutDesc.getNumOfAttributes(); ++i)
		//	{
		//		glEnableVertexAttribArray(i);
		//		checkErrors();
		//		ShaderLayout layout = layoutDesc.getAttribute(i);
		//		glVertexAttribPointer(
		//			i,
		//			getAttirbuteMemberCount(layout.type),
		//			GL_FLOAT, // TODO
		//			false, // TODO
		//			layoutSize,
		//			(void*)offset
		//		);
		//		checkErrors();
		//		offset += getTypeSize(layout.type);
		//	}
		//	tempVBO.unbind();
		//	glBindVertexArray(0);
		//	checkErrors();
		//	return std::make_unique<MaterialContextImpl>(material, this, vao);
		//}



	
	}
}
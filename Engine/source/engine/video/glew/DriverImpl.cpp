#include <stdafx.h>
#include <engine/video/glew/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

#include <engine/Context.h>

#include <engine/video/BufferContext.h>
#include <engine/video/Effect.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/Material.h>
#include <engine/video/RenderTarget.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderResourceBindingData.h>
#include <engine/video/AttributeFormat.h>
#include <engine/video/VertexBuffer.h>

#include <engine/video/glew/GLSLEffectCompilationData.h>
#include <engine/video/glew/GLSLResourceBinding.h>
#include <engine/video/glew/GLSLResourceHandler.h>
#include <engine/video/glew/GLSLVSCompilationData.h>
#include <engine/video/glew/GLSLFSCompilationData.h>
#include <engine/video/glew/IndexBufferObject.h>
#include <engine/video/glew/VertexBufferObject.h>

#include <engine/video/GPUTypes.h>

#include <engine/view/Console.h>

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
			if((err = glGetError()) != GL_NO_ERROR)
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
			engine::Context::console()->print("VAO:         %", currentVAO);
			engine::Context::console()->print("VBO:         %", currentVBO);
			engine::Context::console()->print("IndexBuffer: %", currentIndexBuffer);
			engine::Context::console()->print("Program:     %", currentProgram);
		}

		void DriverImpl::printInfo()
		{
			engine::Context::console()->print("Opengl version %", (char*)glGetString(GL_VERSION));
		}

		std::pair<int32_t, int32_t> DriverImpl::getOpenglMajorMinorVersion(DriverVersion version) const
		{
			switch(version)
			{
				case engine::DriverVersion::OpenGL_Core_3_2: return std::make_pair(3, 2); break;
				case engine::DriverVersion::OpenGL_Core_3_3: return std::make_pair(3, 3); break;
				case engine::DriverVersion::OpenGL_Core_4_0: return std::make_pair(4, 0); break;
				case engine::DriverVersion::OpenGL_Core_4_1: return std::make_pair(4, 1); break;
				case engine::DriverVersion::OpenGL_Core_4_2: return std::make_pair(4, 2); break;
				case engine::DriverVersion::OpenGL_Core_4_3: return std::make_pair(4, 3); break;
				case engine::DriverVersion::OpenGL_ES_2_0:   return std::make_pair(2, 0); break;
				case engine::DriverVersion::OpenGL_ES_3_0:   return std::make_pair(3, 0); break;
				case engine::DriverVersion::DirectX11:
				default:
				FAIL("Unknown opengl version.");
				break;
			}
			return std::make_pair(0, 0);
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

		void DriverImpl::compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat&)
		{
			bool optionsOk = checkShaderOptions(options);
			ASSERT(optionsOk);

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

		bool DriverImpl::checkShaderOptions(const ShaderCompileOptions& options) const
		{
			ShaderVersion version = options.getVersion();
			DeviceParameters deviceParameters = getDeviceParameters();
			bool result = false;
			switch(version)
			{
				case engine::ShaderVersion::GLSL_100:
				if(deviceParameters.version == DriverVersion::OpenGL_ES_2_0
				   || deviceParameters.version != DriverVersion::OpenGL_ES_3_0)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_150:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_3_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_3_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_0
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_1
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_300:
				if(deviceParameters.version == DriverVersion::OpenGL_ES_3_0)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_330:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_3_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_0
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_1
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_400:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_0
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_1
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_410:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_1
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_420:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_2
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_430:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_3
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_440:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_4
				   || deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::GLSL_450:
				if(deviceParameters.version == DriverVersion::OpenGL_Core_4_5)
				{
					result = true;
				}
				break;
				case engine::ShaderVersion::HLSL_4_0_level_9_1:
				case engine::ShaderVersion::HLSL_4_0_level_9_3:
				case engine::ShaderVersion::HLSL_4_0:
				case engine::ShaderVersion::HLSL_4_1:
				case engine::ShaderVersion::HLSL_5_0:
				case engine::ShaderVersion::Num:
				default:
				FAIL("Not an opengl shader");
				break;
			}
			return result;
		}

		bool DriverImpl::checkDeviceSetupImpl()
		{
			printInfo();

			DeviceParameters deviceParameters = getDeviceParameters();
			std::pair<int32_t, int32_t> version = getOpenglMajorMinorVersion(deviceParameters.version);
			bool isOk = true;
			GLint majorVersion = 0;
			GLint minorVersion = 0;
			glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
			glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
			isOk = (majorVersion == version.first) && (minorVersion == version.second);
			return isOk;
		}

		std::unique_ptr<ShaderResourceHandler> DriverImpl::createShaderResourceHandlerImpl()
		{
			return std::unique_ptr<ShaderResourceHandler>(new GLSLResourceHandler(this));
		}

		std::unique_ptr<ShaderResourceBinding> DriverImpl::bindResourceImpl(const ShaderResourceDescription& desc, Effect* effect)
		{
#ifdef _DEBUG
			return bindResourceImplDebug(desc, effect);
#else
			return bindResourceImplRelease(desc, effect);
#endif
		}

		std::unique_ptr<ShaderResourceBinding> DriverImpl::bindResourceImplDebug(const ShaderResourceDescription& desc, Effect* effect)
		{
#ifdef _DEBUG
			const std::string uniformName = desc.getName();
			const GLSLEffectCompilationData* glslEffectData = static_cast<const GLSLEffectCompilationData*>(effect->getCompilationData());
			GLint location = glGetUniformLocation(glslEffectData->getProgramId(), uniformName.c_str());
			if(desc.getResourceBindingData().hasLayout())
			{
				ASSERT(desc.getResourceBindingData().getLayout() == location);
			}
			return std::unique_ptr<ShaderResourceBinding>(new GLSLResourceBinding(location));
#else
			HARD_FAIL("Debug code on Release context");
			return nullptr;
#endif
		}

		std::unique_ptr<ShaderResourceBinding> DriverImpl::bindResourceImplRelease(const ShaderResourceDescription& desc, Effect* effect)
		{
#ifndef _DEBUG
			if(desc.getResourceBindingData().hasLayout())
			{
				return std::unique_ptr<ShaderResourceBinding>(new GLSLResourceBinding(desc.getResourceBindingData().getLayout()));
			}
			else
			{
				const std::string uniformName = desc.getName();
				const GLSLEffectCompilationData* glslEffectData = static_cast<const GLSLEffectCompilationData*>(effect->getCompilationData());
				GLint location = glGetUniformLocation(glslEffectData->getProgramId(), uniformName.c_str());
				return std::unique_ptr<ShaderResourceBinding>(new GLSLResourceBinding(location));
			}
#else
			HARD_FAIL("Release code on debug context");
			return nullptr;
#endif
		}
	}
}

#else

#include <engine/video/glew/empty/DriverImpl.cpp>

#endif
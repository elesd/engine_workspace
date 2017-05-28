#include <stdafx.h>

#include <engine/video/winapi/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI
#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/winapi/WindowImpl.h>

#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/ShaderCompiler.h>
#include <engine/video/winapi/BufferDescUtils.h>
#include <engine/video/winapi/HLSLVSCompilationData.h>
#include <engine/video/winapi/HLSLFSCompilationData.h>
#include <engine/video/winapi/RenderTargetImpl.h>
#include <engine/video/winapi/TextureImpl.h>

#include <engine/utils/ScopeExit.h>

#include <d3d11.h>
#include <D3Dcompiler.h>

namespace
{
	struct CompileDataWrapper
	{
		const void* data = nullptr;
		size_t dataSize;
		D3D_SHADER_MACRO* defines = nullprt;
		ID3DInclude* includes = nullptr;
		std::string entryPoint;
		std::string target;
		uint32_t flags1;
		uint32_t flags2;
		ID3DBlob* errorMessage = nullptr;

		~CompileDataWrapper()
		{
			delete[] defines;
			if(errorMessage)
			{
				errorMessage->Release();
			}
		}
	};
	const std::map<engine::ShaderVersion, std::string> vertexShaderVersionMap = {
		{engine::ShaderVersion::HLSL_4_0_level_9_1, "vs_4_0_level_9_1"},
		{engine::ShaderVersion::HLSL_4_0_level_9_3, "vs_4_0_level_9_3"},
		{engine::ShaderVersion::HLSL_4_0, "vs_4_0"},
		{engine::ShaderVersion::HLSL_4_1, "vs_4_1"},
		{engine::ShaderVersion::HLSL_4_1, "vs_5_0"},
	};

	const std::map<engine::ShaderVersion, std::string> fragmentShaderVersionMap = {
		{engine::ShaderVersion::HLSL_4_0_level_9_1, "ps_4_0_level_9_1"},
		{engine::ShaderVersion::HLSL_4_0_level_9_3, "ps_4_0_level_9_3"},
		{engine::ShaderVersion::HLSL_4_0, "ps_4_0"},
		{engine::ShaderVersion::HLSL_4_1, "ps_4_1"},
		{engine::ShaderVersion::HLSL_4_1, "ps_5_0"},
	};

	std::string getTargetFromData(const engine::Shader* shader, const engine::ShaderCompileOptions& options)
	{
		using engine::ShaderType;
		std::string target = "";
		switch(shader->getShaderType())
		{
			case ShaderType::VertexShader:
			{
				auto it = vertexShaderVersionMap.find(options.getVersion());
				HARD_ASSERT(it != vertexShaderVersionMap.end());
				target = it->second;
			}
			break;
			case ShaderType::FragmentShader:
			{
				auto it = fragmentShaderVersionMap.find(options.getVersion());
				HARD_ASSERT(it != fragmentShaderVersionMap.end());
				target = it->second;
			}
			break;
			default: HARD_FAIL("Not implemented shader type");
		}
		return target;
	}

	void fillSourceCodeData(engine::Shader* shader, const engine::ShaderCompileOptions& options, CompileDataWrapper& compileData)
	{
		compileData.target = getTargetFromData(shader, options);

		const std::string& code = shader->getCode();
		compileData.data = code.c_str();
		compileData.dataSize = code.size();
		compileData.entryPoint = shader->getMainFunctionName();
	}

	void fillShaderDefines(const engine::ShaderCompileOptions& options, CompileDataWrapper& compileData)
	{
		if(options.getDefines().empty() == false)
		{
			compileData.defines = new D3D_SHADER_MACRO[options.getDefines().size()];
			for(size_t i = 0; i < options.getDefines().size(); ++i)
			{
				const std::string& define = options.getDefines()[i];
				compileData.defines[i].Name = define.c_str();
				compileData.defines[i].Definition = "1";
			}
		}
	}

	uint32_t getCompilationFlags(const engine::ShaderCompileOptions& options)
	{
		using engine::ShaderCompileFlag;
		uint32_t compileFlags = 0;
		if(options.getFlags().empty() == false)
		{
			for(ShaderCompileFlag flag : options.getFlags())
			{
				switch(flag)
				{
					case ShaderCompileFlag::Debug: compileFlags |= D3DCOMPILE_DEBUG; break;
					case ShaderCompileFlag::PackMatrixColumnMajor: compileFlags |= D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR; break;
					case ShaderCompileFlag::PackMatrixRowMajor: compileFlags |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR; break;
					case ShaderCompileFlag::SkipOptimization: compileFlags |= D3DCOMPILE_SKIP_OPTIMIZATION; break;
					case  ShaderCompileFlag::WarningAreErrors: compileFlags |= D3DCOMPILE_WARNINGS_ARE_ERRORS; break;
					default: FAIL("Unknown shader compiler flag"); break;
				}
			}
		}
		return compileFlags;
	}

	void fillCompilationData(const engine::ShaderCompileOptions& options, CompileDataWrapper& compileData)
	{
		fillShaderDefines(options, compileData);
		compileData.flags1 = getCompilationFlags(options);
		compileData.flags2 = 0;
		compileData.includes = nullptr;
	}

	std::unique_ptr<engine::ShaderCompilationData> createShaderCompilationData(engine::ShaderType type, const engine::ShaderCompileOptions& options)
	{
		std::unique_ptr<engine::ShaderCompilationData> resultData;
		using engine::ShaderType;
		switch(type)
		{
			case ShaderType::VertexShader: resultData.reset(new engine::winapi::HLSLVSCompilationData(options)); break;
			case ShaderType::FragmentShader: resultData.reset(new engine::winapi::HLSLFSCompilationData(options)); break;
			default: FAIL("Unimplemented shader type"); break;
		}
		return resultData;
	}

	std::string getStringFromBlob(ID3DBlob* blob)
	{
		size_t bufferSize = blob->GetBufferSize();
		std::vector<char> strData(bufferSize, '\0');
		std::memcpy(strData.data(), blob->GetBufferPointer(), bufferSize);
		std::string str(strData.data());
		return str;
	}
}

namespace engine
{
	namespace winapi
	{
		struct DriverImplPrivate
		{
			IDXGISwapChain* swapChain = nullptr;
			ID3D11Device* device = nullptr;
			ID3D11DeviceContext* deviceContext = nullptr;
			std::unique_ptr<RenderTarget> backBuffer = nullptr;
		};

		DriverImpl::DriverImpl() :
			_members(new DriverImplPrivate())
		{

		}
		DriverImpl::~DriverImpl()
		{
			if(_members)
			{
				if(_members->swapChain)
				{
					_members->swapChain->Release();
				}
				if(_members->device)
				{
					_members->device->Release();
				}
				if(_members->deviceContext)
				{
					_members->deviceContext->Release();
				}
				delete _members;
			}
		}

		void DriverImpl::initImpl(const DriverInitParameters& params, Window *window)
		{
			createDevice();
			createSwapChain(params, window);
			initViewPort(window);
			initRenderTarget();
		}

		void DriverImpl::setViewPortImpl(int32_t topX, int32_t topY, int32_t width, int32_t height)
		{
			D3D11_VIEWPORT viewport = {0};

			viewport.TopLeftX = float(topX);
			viewport.TopLeftY = float(topY);
			viewport.Width = float(width);
			viewport.Height = float(height);

			_members->deviceContext->RSSetViewports(1, &viewport);
		}

		void DriverImpl::createDevice()
		{
			uint32_t flags = 0;
#ifdef _DEBUG
			flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			// create a device, device context and swap chain using the information in the scd struct
			HRESULT result = D3D11CreateDevice(nullptr,
											   D3D_DRIVER_TYPE_HARDWARE,
											   nullptr,
											   flags,
											   nullptr,
											   0,
											   D3D11_SDK_VERSION,
											   &_members->device,
											   nullptr,
											   &_members->deviceContext);
			if(FAILED(result))
			{
				std::ostringstream os;
				os << "Driver initialization failed at device creation with error code: " << result;
				throw InitializationError(os.str());
			}
		}

		void DriverImpl::createSwapChain(const DriverInitParameters& params, Window *window)
		{

			DXGI_SWAP_CHAIN_DESC scd = {0};

			winapi::WindowImpl *winapiWindow = static_cast<winapi::WindowImpl*>(window);

			// fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = BufferDescUtils::EncodeDesc(params.description);
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = winapiWindow->getWindowHandler();	// the window to be used
			scd.SampleDesc.Count = params.sampleCount;				// how many multisamples
			scd.SampleDesc.Quality = 0;				// how many multisamples
			scd.Windowed = !winapiWindow->isFullScreen();			// windowed/full-screen mode
																	// TODO Setup buffer widht, height
			scd.BufferDesc.Height = winapiWindow->getHeight();
			scd.BufferDesc.Width = winapiWindow->getWidth();
			scd.BufferDesc.RefreshRate.Numerator = 60;
			scd.BufferDesc.RefreshRate.Denominator = 1;
			IDXGIDevice *device = nullptr;
			HRESULT hr = _members->device->QueryInterface(__uuidof(IDXGIDevice), (void **)&device);
			if(FAILED(hr))
			{
				std::ostringstream os;
				os << "Driver initialization failed at swap chain creation [at dxgi device] with error code: " << hr;
				throw InitializationError(os.str());
			}
			IDXGIAdapter *adapter = nullptr;
			hr = device->GetAdapter(&adapter);
			if(FAILED(hr))
			{
				std::ostringstream os;
				os << "Driver initialization failed at swap chain creation [at dxgi adapter] with error code: " << hr;
				throw InitializationError(os.str());
			}
			IDXGIFactory *objectFactory = nullptr;
			adapter->GetParent(__uuidof(IDXGIFactory), (void **)&objectFactory);
			hr = objectFactory->CreateSwapChain(_members->device, &scd, &_members->swapChain);
			if(FAILED(hr))
			{
				std::ostringstream os;
				os << "Driver initialization failed at swap chain creation with error code: " << hr;
				throw InitializationError(os.str());
			}
		}

		void DriverImpl::initRenderTarget()
		{
			createBackBufferRenderTarget();

			setRenderTarget(_members->backBuffer.get());
		}

		std::unique_ptr<TextureImpl> DriverImpl::createBackBufferTexture()
		{
			ID3D11Texture2D* backBufferTexture = nullptr;
			HRESULT hr;
			hr = _members->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
			if(FAILED(hr))
			{
				std::ostringstream os;
				os << "Back buffer texture not found, error code: " << hr;
				throw InitializationError(os.str());
			}

			std::unique_ptr<TextureImpl> result(new TextureImpl(backBufferTexture));
			return result;
		}

		void DriverImpl::createBackBufferRenderTarget()
		{
			std::unique_ptr<TextureImpl> texture = createBackBufferTexture();

			_members->backBuffer = createRenderTarget(texture.get());
			if(_members->backBuffer == nullptr)
			{
				std::ostringstream os;
				os << "Back buffer render target cannot be created!";
				throw InitializationError(os.str());
			}
		}

		void DriverImpl::initViewPort(Window *window)
		{
			setViewPort(0, 0, window->getWidth(), window->getHeight());
		}

		void DriverImpl::drawImpl(const VertexBuffer* verticies, const IndexBuffer* indicies)
		{
			 
		}

		void DriverImpl::setRenderTargetImpl(RenderTarget* renderTarget)
		{
			RenderTargetImpl* rt = static_cast<RenderTargetImpl*>(renderTarget);
			ID3D11RenderTargetView *target = rt->getRenderTargetView();
			_members->deviceContext->OMSetRenderTargets(1, &target, nullptr);
		}

		void DriverImpl::setShaderImpl(Shader* shader, const std::string& techniqueName)
		{
			switch(shader->getShaderType())
			{
				case ShaderType::VertexShader:
				{
					const HLSLVSCompilationData* data = static_cast<const HLSLVSCompilationData*>(shader->getCompilationData(techniqueName));
					ASSERT(data->compilationWasSuccessfull());
					_members->deviceContext->VSSetShader(data->getShaderInterface(), nullptr, 0);
				}
				break;
				case ShaderType::FragmentShader:
				{
					const HLSLFSCompilationData* data = static_cast<const HLSLFSCompilationData*>(shader->getCompilationData(techniqueName));
					ASSERT(data->compilationWasSuccessfull());
					_members->deviceContext->PSSetShader(data->getShaderInterface(), nullptr, 0);
				}
				break;
				default:
				FAIL("Unimplemented shader type"); 
				break;
			}
		}

		std::unique_ptr<RenderTarget> DriverImpl::createRenderTargetImpl(Texture* texture)
		{
			std::unique_ptr<RenderTarget> result;
			ID3D11RenderTargetView *winapiRenderTarget = nullptr;
			TextureImpl* concrateTexture = static_cast<TextureImpl*>(texture);
			HRESULT hr = _members->device->CreateRenderTargetView(concrateTexture->getTextureInterface(), nullptr, &winapiRenderTarget);
			if(SUCCEEDED(hr))
			{
				result.reset(new RenderTargetImpl(winapiRenderTarget));
			}
			return result;
		}

		void DriverImpl::compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options)
		{
			CompileDataWrapper compileData;
			fillSourceCodeData(shader, options, compileData);
			fillCompilationData(options, compileData);

			ID3DBlob* compiledCode = nullptr;
			HRESULT result = D3DCompile(compileData.data,
										compileData.dataSize,
										nullptr,
										compileData.defines,
										compileData.includes,
										compileData.entryPoint.c_str(),
										compileData.target.c_str(),
										compileData.flags1,
										compileData.flags2,
										&compiledCode,
										&compileData.errorMessage);

			std::unique_ptr<ShaderCompilationData> resultData = createShaderCompilationData(shader->getShaderType(), options);
			
			if(FAILED(result))
			{
				resultData->setError(getStringFromBlob(compileData.errorMessage));
				compiledCode->Release();
			}
			else
			{
				switch(shader->getShaderType())
				{
					case ShaderType::FragmentShader: createD3DFragmentShaderInto(compiledCode, resultData.get()); break;
					case ShaderType::VertexShader: createD3DVertexShaderInto(compiledCode, resultData.get()); break;
					default: FAIL("Unimplemented shader type"); break;
				}
				compiledCode = nullptr;
			}

			shader->setCompiled(techniqueName, std::move(resultData));
		}

		void DriverImpl::createD3DFragmentShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const
		{
			ID3D11PixelShader* d3dShader = nullptr;
			HRESULT result = _members->device->CreatePixelShader(compiledCode, compiledCode->GetBufferSize(), nullptr, &d3dShader);
			if(FAILED(result))
			{
				resultData->setError("Shader creation error");
				d3dShader->Release();
				compiledCode->Release();
			}
			else
			{
				static_cast<HLSLFSCompilationData*>(resultData)->setOk(compiledCode, d3dShader);
			}
		}

		void DriverImpl::createD3DVertexShaderInto(ID3DBlob* compiledCode, ShaderCompilationData* resultData) const
		{
			ID3D11VertexShader* d3dShader = nullptr;
			HRESULT result = _members->device->CreateVertexShader(compiledCode, compiledCode->GetBufferSize(), nullptr, &d3dShader);
			if(FAILED(result))
			{
				resultData->setError("Shader creation error");
				d3dShader->Release();
				compiledCode->Release();
			}
			else
			{
				static_cast<HLSLVSCompilationData*>(resultData)->setOk(compiledCode, d3dShader);
			}
		}
	}
}
#else

#include <engine/video/winapi/empty/DriverImpl.cpp>

#endif
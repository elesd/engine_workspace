#include <stdafx.h>

#include <engine/video/winapi/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI
#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/winapi/WindowImpl.h>
#include <engine/video/winapi/BufferDescUtils.h>
#include <engine/video/winapi/RenderTargetImpl.h>
#include <engine/video/winapi/TextureImpl.h>

#include <d3d11.h>

namespace engine
{
	namespace winapi
	{
		struct DriverImplPrivate
		{
			IDXGISwapChain* swapChain = nullptr;
			ID3D11Device* device = nullptr;
			ID3D11DeviceContext* deviceContext = nullptr;
			std::unique_ptr<RenderTargetImpl> backBuffer = nullptr;
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

		void DriverImpl::createBackBufferRenderTarget()
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

			TextureImpl texture(backBufferTexture);
			ID3D11RenderTargetView *backbuffer = nullptr;
			hr = _members->device->CreateRenderTargetView(backBufferTexture, nullptr, &backbuffer);
			if(FAILED(hr))
			{
				std::ostringstream os;
				os << "Back buffer render target cannot be created, error code: " << hr;
				throw InitializationError(os.str());
			}
			_members->backBuffer = std::make_unique<RenderTargetImpl>(backbuffer);
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

		void DriverImpl::setMaterialImpl(Material* material)
		{
			FAIL("Not implemented");
		}

	}
}
#else

#include <engine/video/winapi/empty/DriverImpl.cpp>

#endif
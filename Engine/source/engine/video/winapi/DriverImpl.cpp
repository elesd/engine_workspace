#include <stdafx.h>

#include <engine/video/winapi/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI
#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Window.h>
#include <engine/view/winapi/WindowImpl.h>
#include <engine/video/winapi/BufferDescUtils.h>

#include <d3d11.h>

namespace engine
{
	namespace winapi
	{
		struct DriverImplPrivate
		{
			IDXGISwapChain *swapChain = nullptr;
			ID3D11Device *device = nullptr;
			ID3D11DeviceContext *deviceContext = nullptr;
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
			DXGI_SWAP_CHAIN_DESC scd = { 0 };

			winapi::WindowImpl *winapiWindow = static_cast<winapi::WindowImpl*>(window);

			// fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = BufferDescUtils::EncodeDesc(params.description);
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = winapiWindow->getWindowHandler();	// the window to be used
			scd.SampleDesc.Count = params.sampleCount;				// how many multisamples
			scd.Windowed = winapiWindow->isFullScreen();            // windowed/full-screen mode

			// create a device, device context and swap chain using the information in the scd struct
			D3D11CreateDeviceAndSwapChain(nullptr,
										  D3D_DRIVER_TYPE_HARDWARE,
										  nullptr,
										  0,
										  nullptr,
										  0,
										  D3D11_SDK_VERSION,
										  &scd,
										  &_members->swapChain,
										  &_members->device,
										  nullptr,
										  &_members->deviceContext);
			if(_members->swapChain == nullptr
			   || _members->device == nullptr
			   || _members->deviceContext == nullptr)
			{
				throw InitializationError("Driver initialization error.");
			}
		}
	}
}
#endif
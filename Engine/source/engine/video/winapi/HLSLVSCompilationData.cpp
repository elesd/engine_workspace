#include <stdafx.h>
#include <engine/video/winapi/HLSLVSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI


#include <d3d11.h>
#include <D3Dcompiler.h>

namespace engine
{
	namespace winapi
	{

		struct HLSLVSCompilationDataPrivate
		{
			ID3DBlob* compiledCode = nullptr;
			ID3D11VertexShader* shader = nullptr;
			ID3D11InputLayout* layout = nullptr;
		};

		HLSLVSCompilationData::HLSLVSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
			, _members(new HLSLVSCompilationDataPrivate())
		{ }

		HLSLVSCompilationData::~HLSLVSCompilationData()
		{
			if(_members)
			{
				if(_members->compiledCode)
				{
					_members->compiledCode->Release();
				}
				if(_members->shader)
				{
					_members->shader->Release();
				}
				if(_members->layout)
				{
					_members->layout->Release();
				}
			}
			delete _members;
		}

		void HLSLVSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11VertexShader* shader, ID3D11InputLayout* layout)
		{
			ShaderCompilationData::setOk();
			_members->compiledCode = compiledCode;
			_members->shader = shader;
			_members->layout = layout;
		}

		ID3D11VertexShader* HLSLVSCompilationData::getShaderInterface() const
		{
			return _members->shader;
		}

		ID3D11InputLayout* HLSLVSCompilationData::getLayoutInterface() const
		{
			return _members->layout;
		}

		void HLSLVSCompilationData::releaseImpl()
		{
			if(_members)
			{
				if(_members->compiledCode)
				{
					_members->compiledCode->Release();
				}
				if(_members->shader)
				{
					_members->shader->Release();
				}
				if(_members->layout)
				{
					_members->layout->Release();
				}
			}
		}
	}
}

#endif
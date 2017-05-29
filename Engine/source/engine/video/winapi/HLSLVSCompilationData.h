#pragma once

#include <engine/video/ShaderCompilationData.h>

struct ID3D10Blob;
struct ID3D11VertexShader;
struct ID3D11InputLayout;

namespace engine
{
	namespace winapi
	{
		class HLSLVSCompilationData : public ShaderCompilationData
		{
		public:
			HLSLVSCompilationData(const ShaderCompileOptions& options);
			~HLSLVSCompilationData() override;

			void setOk(ID3D10Blob* compiledCode, ID3D11VertexShader* shader, ID3D11InputLayout* layout);
			ID3D11VertexShader* getShaderInterface() const;
			ID3D11InputLayout* getLayoutInterface() const;
		private:
			struct HLSLVSCompilationDataPrivate* _members = nullptr;
		};
	}
}
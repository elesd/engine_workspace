#pragma once
#if ENGINE_USE_WINAPI

#	include <windows.h>
#   if ENGINE_USE_WINAPI
#       include <d3d11.h>
#   endif
#else
#define NULL_DEF(Type) using Type = void*;
#define NULL_VALUE_DEF(Type) struct Type {};

NULL_DEF(HWND)
NULL_DEF(UINT)
NULL_DEF(WPARAM)
NULL_DEF(LPARAM)
NULL_DEF(HINSTANCE)
NULL_DEF(LPSTR)
NULL_DEF(ID3DBlob)
NULL_VALUE_DEF(D3D11_BUFFER_DESC)
NULL_DEF(D3D11_SUBRESOURCE_DATA)

#undef NULL_DEF

#endif
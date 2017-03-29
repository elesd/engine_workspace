#if ENGINE_USE_WINAPI

#	include <windows.h>

#else
#define NULL_DEF(Type) using Type = void*;

NULL_DEF(HWND)
NULL_DEF(UINT)
NULL_DEF(WPARAM)
NULL_DEF(LPARAM)
NULL_DEF(HINSTANCE)
NULL_DEF(LPSTR)

#undef NULL_DEF

#endif
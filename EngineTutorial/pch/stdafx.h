// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// Global
#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

// C includes
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstring>

#ifdef WIN32
#   include <tchar.h>
#endif

// C++ includes
#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <list>
#include <set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include <iomanip>

// Math

#include <glm/gtc/type_precision.hpp>

// Macros

#define ASSERT(cond) assert(cond)
#define HARD_ASSERT(cond) assert(cond)
#define FAIL(msg) assert(false && msg)
#define HARD_FAIL(msg) assert(false && msg)

#include "TutorialConfig.h"
#include <engine/EngineConfig.h>

#ifdef TUTORIAL_USE_WINAPI
#include <Windows.h>
#endif

#include <engine/Types.h>

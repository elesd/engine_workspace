// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//



// C includes
#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>


#ifdef WIN32
#   include <tchar.h>
#endif

// C++ includes
#include <algorithm>
#include <array>
#include <deque>
#include <fstream>
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

// Engine files
#include <engine/EngineConfig.h>
#include <engine/Types.h>
#include <engine/utils/Common.h>

// Math
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_precision.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
// Macros

#define ASSERT(cond) assert(cond)
#define HARD_ASSERT(cond) assert(cond)
#define FAIL(msg) assert(false && msg)
#define HARD_FAIL(msg) assert(false && msg)

#define UNSUPPORTED_ERROR() HARD_FAIL("Unsupported feature usage")
#define INACTIVE_MODULE_ERROR() HARD_FAIL("Module is inactive")



// Platform specific codes
#include <stdafx_win.h>
#include <stdafx_glew.h>


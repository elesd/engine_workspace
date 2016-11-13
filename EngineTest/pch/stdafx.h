// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// C includes
#include <cassert>
#include <cstdio>
#include <cstdint>

#include <tchar.h>


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


// For engine
#include "engine/test/GameAssertException.h"

// Macros

#define ASSERT(cond) if(!(cond)) throw engine::test::GameAssertException(engine::test::GameAssertException::Type::Normal, #cond, __FILE__, __LINE__)
#define HARD_ASSERT(cond) if(!(cond)) throw engine::test::GameAssertException(engine::test::GameAssertException::Type::Hard, #cond, __FILE__, __LINE__)
#define FAIL(msg) throw engine::test::GameAssertException(engine::test::GameAssertException::Type::Normal, #msg, __FILE__, __LINE__)
#define HARD_FAIL(msg) throw engine::test::GameAssertException(engine::test::GameAssertException::Type::Hard, #msg, __FILE__, __LINE__)

// Fot tests

#define private public
#define protected public
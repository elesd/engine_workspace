#pragma once

#if ENGINE_USE_GLEW
#include <GL/glew.h>
#else
#define NULL_DEF(Type) using Type = void*;
#define NULL_VALUE_DEF(Type) struct Type {};

NULL_DEF(GLUint)
#endif
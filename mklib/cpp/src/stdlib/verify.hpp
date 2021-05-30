#pragma once


#ifdef NDEBUG
#undef NDEBUG
#define NDEBUG_REMOVED
#endif


#include "assert.hpp"


#define MK_STDLIB_VERIFY MK_STDLIB_ASSERT


#ifdef NDEBUG_REMOVED
#define NDEBUG
#endif

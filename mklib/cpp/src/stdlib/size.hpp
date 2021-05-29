#pragma once


#include "architecture.hpp"


namespace mk
{
	namespace stdlib
	{


		#if MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_I386


		typedef unsigned int size_t;
		typedef signed int ptrdiff_t;
		typedef unsigned int uintptr_t;
		typedef signed int intptr_t;


		#elif MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_AMD64


		typedef unsigned __int64 size_t;
		typedef signed __int64 ptrdiff_t;
		typedef unsigned __int64 uintptr_t;
		typedef signed __int64 intptr_t;


		#endif


	}
}

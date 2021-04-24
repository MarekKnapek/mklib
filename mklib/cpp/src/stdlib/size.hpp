#pragma once


#include "architecture.hpp"


namespace mk
{
	namespace stdlib
	{


		#if MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_I386


		typedef unsigned int size_t;
		typedef signed int ptrdiff_t;


		#elif MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_AMD64


		typedef unsigned __int64 size_t;
		typedef signed __int64 ptrdiff_t;


		#endif


	}
}

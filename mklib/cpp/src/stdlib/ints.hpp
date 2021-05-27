#pragma once


#include "architecture.hpp"


namespace mk
{
	namespace stdlib
	{


		typedef unsigned char uint8_t;
		typedef unsigned short int uint16_t;
		typedef unsigned int uint32_t;
		typedef unsigned long long int uint64_t;

		typedef signed char int8_t;
		typedef signed short int int16_t;
		typedef signed int int32_t;
		typedef signed long long int int64_t;


		#if MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_I386


		typedef unsigned int uintptr_t;


		#elif MK_STDLIB_ARCHITECTURE == MK_STDLIB_ARCHITECTURE_AMD64


		typedef unsigned __int64 uintptr_t;


		#endif


	}
}

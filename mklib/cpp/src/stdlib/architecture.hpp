#pragma once


#define MK_STDLIB_ARCHITECTURE_I386 2
#define MK_STDLIB_ARCHITECTURE_AMD64 3

#ifdef _M_IX86
# define MK_STDLIB_ARCHITECTURE MK_STDLIB_ARCHITECTURE_I386
#else
# ifdef _M_X64
#  define MK_STDLIB_ARCHITECTURE MK_STDLIB_ARCHITECTURE_AMD64
# else
#  error Unknown architecture.
# endif
#endif

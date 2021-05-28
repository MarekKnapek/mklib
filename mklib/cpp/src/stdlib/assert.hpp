// no pragma once


namespace mk { namespace stdlib { void assert_failed() noexcept; } }


#undef MK_STDLIB_ASSERT


#ifdef NDEBUG


#define MK_STDLIB_ASSERT(X) ((void)0)


#else


#define MK_STDLIB_ASSERT(X) do{ if(X) {} else [[unlikely]] { mk::stdlib::assert_failed(); } }while(false)


#endif

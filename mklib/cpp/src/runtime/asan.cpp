#include "asan.hpp"


#if defined(__SANITIZE_ADDRESS__)
extern "C" void __asan_poison_memory_region(void const*, mk::stdlib::size_t);
extern "C" void __asan_unpoison_memory_region(void const*, mk::stdlib::size_t);
#endif


void mk::runtime::asan_poison_memory_region(void const* const& addr, mk::stdlib::size_t const& size) noexcept
{
#if defined(__SANITIZE_ADDRESS__)
	__asan_poison_memory_region(addr, size);
#else
	(void)addr;
	(void)size;
#endif
}

void mk::runtime::asan_unpoison_memory_region(void const* const& addr, mk::stdlib::size_t const& size) noexcept
{
#if defined(__SANITIZE_ADDRESS__)
	__asan_unpoison_memory_region(addr, size);
#else
	(void)addr;
	(void)size;
#endif
}

#include "cstdlib.hpp"

#include "heap/heap_multi_threaded.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{


			mk::stdlib::heap_multi_threaded_t g_heap;


		}
	}
}


mk::stdlib::cstdlib_init_t::cstdlib_init_t() noexcept
{
	mk::stdlib::cstdlib_init();
}

mk::stdlib::cstdlib_init_t::~cstdlib_init_t() noexcept
{
	mk::stdlib::cstdlib_deinit();
}


void mk::stdlib::cstdlib_init() noexcept
{
	mk::stdlib::impl::g_heap = mk::stdlib::heap_multi_threaded_t::make();
}

void mk::stdlib::cstdlib_deinit() noexcept
{
	mk::stdlib::impl::g_heap = mk::stdlib::heap_multi_threaded_t{};
}


[[nodiscard]] void* mk::stdlib::malloc(mk::stdlib::size_t const& count) noexcept
{
	return mk::stdlib::impl::g_heap.alloc(count);
}

void mk::stdlib::free(void const* const& ptr) noexcept
{
	mk::stdlib::impl::g_heap.free(ptr);
}

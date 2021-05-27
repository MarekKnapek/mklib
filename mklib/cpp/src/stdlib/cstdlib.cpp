#include "cstdlib.hpp"

#include "heap/heap_multi_threaded.hpp"
#include "type_traits/aligned_storage.hpp"
#include "memory.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{


			mk::stdlib::aligned_storage_helper_t<mk::stdlib::heap_multi_threaded_t> g_heap;

			
			mk::stdlib::heap_multi_threaded_t& get_global_heap() noexcept;


		}
	}
}


mk::stdlib::heap_multi_threaded_t& mk::stdlib::impl::get_global_heap() noexcept
{
	return *reinterpret_cast<mk::stdlib::heap_multi_threaded_t*>(g_heap.m_data);
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
	mk::stdlib::construct_at(&mk::stdlib::impl::get_global_heap());
}

void mk::stdlib::cstdlib_deinit() noexcept
{
	mk::stdlib::destroy(mk::stdlib::impl::get_global_heap());
}


[[nodiscard]] void* mk::stdlib::malloc(mk::stdlib::size_t const& count) noexcept
{
	void* const ptr = mk::stdlib::impl::get_global_heap().alloc(count);
	return ptr;
}

void mk::stdlib::free(void const* const& ptr) noexcept
{
	mk::stdlib::impl::get_global_heap().free(ptr);
}

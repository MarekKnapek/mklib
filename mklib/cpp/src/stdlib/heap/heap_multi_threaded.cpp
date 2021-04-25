#include "heap_multi_threaded.hpp"

#include "../../win/kernel32/heap.hpp"
#include "../assert.hpp"
#include "../utility/swap.hpp"


mk::stdlib::heap_multi_threaded_t::heap_multi_threaded_t() noexcept :
	m_heap(mk::win::kernel32::heap_create(mk::win::kernel32::heap_create_t::generate_exceptions, 0, 0))
{
	MK_STDLIB_ASSERT(m_heap);
}

mk::stdlib::heap_multi_threaded_t::heap_multi_threaded_t(mk::stdlib::heap_multi_threaded_t&& other) noexcept :
	mk::stdlib::heap_multi_threaded_t()
{
	swap(other);
}

mk::stdlib::heap_multi_threaded_t& mk::stdlib::heap_multi_threaded_t::operator=(mk::stdlib::heap_multi_threaded_t&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

mk::stdlib::heap_multi_threaded_t::~heap_multi_threaded_t() noexcept
{
	if(!*this)
	{
		return;
	}
	bool const destroyed = mk::win::kernel32::heap_destroy(m_heap);
	MK_STDLIB_ASSERT(destroyed);
}

mk::stdlib::heap_multi_threaded_t::operator bool() const noexcept
{
	return !!m_heap;
}

void mk::stdlib::heap_multi_threaded_t::swap(mk::stdlib::heap_multi_threaded_t& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_heap, other.m_heap);
}


[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::alloc(mk::stdlib::size_t const& bytes) noexcept
{
	void* const mem = mk::win::kernel32::heap_alloc(m_heap, mk::win::kernel32::heap_alloc_t::generate_exceptions, bytes);
	MK_STDLIB_ASSERT(mem);
	return mem;
}

[[nodiscard]] mk::stdlib::size_t mk::stdlib::heap_multi_threaded_t::size(void const* const& mem) const noexcept
{
	return mk::win::kernel32::heap_size(m_heap, mk::win::kernel32::heap_size_t::none, mem);
}

[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	return mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::none, mem, bytes);
}

[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	return mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::in_place_only, mem, bytes);
}

void mk::stdlib::heap_multi_threaded_t::free(void* const& mem) noexcept
{
	bool const freed = mk::win::kernel32::heap_free(m_heap, mk::win::kernel32::heap_free_t::none, mem);
	MK_STDLIB_ASSERT(freed);
}

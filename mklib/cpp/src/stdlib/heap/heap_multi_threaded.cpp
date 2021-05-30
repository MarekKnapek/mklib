#include "heap_multi_threaded.hpp"

#include "../../win/kernel32/heap.hpp"
#include "../assert.hpp"
#include "../utility/swap.hpp"


mk::stdlib::heap_multi_threaded_t::heap_multi_threaded_t() noexcept :
	m_heap()
{
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

void mk::stdlib::heap_multi_threaded_t::swap(mk::stdlib::heap_multi_threaded_t& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_heap, other.m_heap);
}

[[nodiscard]] mk::stdlib::heap_multi_threaded_t::operator bool() const noexcept
{
	return !!m_heap;
}


[[nodiscard]] mk::stdlib::heap_multi_threaded_t mk::stdlib::heap_multi_threaded_t::make() noexcept
{
	mk::win::kernel32::heap_create_t const options = mk::win::kernel32::heap_create_t::none;
	mk::stdlib::size_t const initial_size = 0;
	mk::stdlib::size_t const maximum_size = 0;
	mk::win::handle_t const heap = mk::win::kernel32::heap_create(options, initial_size, maximum_size);
	MK_STDLIB_ASSERT(heap);
	return mk::stdlib::heap_multi_threaded_t{heap};
}

[[nodiscard]] mk::win::handle_t const& mk::stdlib::heap_multi_threaded_t::get() const noexcept
{
	return m_heap;
}


[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::alloc(mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* const mem = mk::win::kernel32::heap_alloc(m_heap, mk::win::kernel32::heap_alloc_t::generate_exceptions, bytes);
	MK_STDLIB_ASSERT(mem);
	return mem;
}

[[nodiscard]] mk::stdlib::size_t mk::stdlib::heap_multi_threaded_t::size(void const* const& mem) const noexcept
{
	MK_STDLIB_ASSERT(*this);
	return mk::win::kernel32::heap_size(m_heap, mk::win::kernel32::heap_size_t::none, mem);
}

[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* const new_mem = mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::generate_exceptions, mem, bytes);
	MK_STDLIB_ASSERT(new_mem);
	return new_mem;
}

[[nodiscard]] void* mk::stdlib::heap_multi_threaded_t::realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	return mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::in_place_only, mem, bytes);
}

void mk::stdlib::heap_multi_threaded_t::free(void const* const& mem) noexcept
{
	MK_STDLIB_ASSERT(*this);
	bool const freed = mk::win::kernel32::heap_free(m_heap, mk::win::kernel32::heap_free_t::none, mem);
	MK_STDLIB_ASSERT(freed);
}


mk::stdlib::heap_multi_threaded_t::heap_multi_threaded_t(mk::win::handle_t const& heap) noexcept :
	m_heap(heap)
{
}

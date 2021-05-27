#include "heap_process.hpp"

#include "../../win/kernel32/heap.hpp"
#include "../assert.hpp"
#include "../utility/swap.hpp"


mk::stdlib::heap_process_t::heap_process_t() noexcept :
	m_heap(mk::win::kernel32::get_process_heap())
{
	MK_STDLIB_ASSERT(m_heap);
}

mk::stdlib::heap_process_t::heap_process_t(mk::stdlib::heap_process_t&& other) noexcept :
	mk::stdlib::heap_process_t()
{
	swap(other);
}

mk::stdlib::heap_process_t& mk::stdlib::heap_process_t::operator=(mk::stdlib::heap_process_t&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

mk::stdlib::heap_process_t::~heap_process_t() noexcept
{
}

mk::stdlib::heap_process_t::operator bool() const noexcept
{
	return !!m_heap;
}

void mk::stdlib::heap_process_t::swap(mk::stdlib::heap_process_t& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_heap, other.m_heap);
}


[[nodiscard]] void* mk::stdlib::heap_process_t::alloc(mk::stdlib::size_t const& bytes) noexcept
{
	void* const mem = mk::win::kernel32::heap_alloc(m_heap, mk::win::kernel32::heap_alloc_t::generate_exceptions, bytes);
	MK_STDLIB_ASSERT(mem);
	return mem;
}

[[nodiscard]] mk::stdlib::size_t mk::stdlib::heap_process_t::size(void const* const& mem) const noexcept
{
	return mk::win::kernel32::heap_size(m_heap, mk::win::kernel32::heap_size_t::none, mem);
}

[[nodiscard]] void* mk::stdlib::heap_process_t::realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	return mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::none, mem, bytes);
}

[[nodiscard]] void* mk::stdlib::heap_process_t::realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	return mk::win::kernel32::heap_realloc(m_heap, mk::win::kernel32::heap_realloc_t::in_place_only, mem, bytes);
}

void mk::stdlib::heap_process_t::free(void const* const& mem) noexcept
{
	bool const freed = mk::win::kernel32::heap_free(m_heap, mk::win::kernel32::heap_free_t::none, mem);
	MK_STDLIB_ASSERT(freed);
}

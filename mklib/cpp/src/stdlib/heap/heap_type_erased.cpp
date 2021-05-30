#include "heap_type_erased.hpp"

#include "../assert.hpp"
#include "../macros.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"
#include "heap_multi_threaded.hpp"
#include "heap_process.hpp"
#include "heap_single_threaded.hpp"
#include "heap_type_erased.hpp"
#include "heap_virtual.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			enum class heap_type_erased_type_t : int
			{
				multi_threaded,
				process,
				single_threaded,
				type_erased,
				virtuall,
			};
		}
	}
}


mk::stdlib::heap_type_erased_t::heap_type_erased_t() noexcept :
	m_heap(),
	m_type()
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_multi_threaded_t& heap) noexcept :
	m_heap(&heap),
	m_type(static_cast<int>(mk::stdlib::impl::heap_type_erased_type_t::multi_threaded))
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_process_t& heap) noexcept :
	m_heap(&heap),
	m_type(static_cast<int>(mk::stdlib::impl::heap_type_erased_type_t::process))
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_single_threaded_t& heap) noexcept :
	m_heap(&heap),
	m_type(static_cast<int>(mk::stdlib::impl::heap_type_erased_type_t::single_threaded))
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_type_erased_t& heap) noexcept :
	m_heap(&heap),
	m_type(static_cast<int>(mk::stdlib::impl::heap_type_erased_type_t::type_erased))
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_virtual_t& heap) noexcept :
	m_heap(&heap),
	m_type(static_cast<int>(mk::stdlib::impl::heap_type_erased_type_t::virtuall))
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_type_erased_t const& other) noexcept :
	m_heap(other.m_heap),
	m_type(other.m_type)
{
}

mk::stdlib::heap_type_erased_t::heap_type_erased_t(mk::stdlib::heap_type_erased_t&& other) noexcept :
	m_heap(mk::stdlib::move(other.m_heap)),
	m_type(mk::stdlib::move(other.m_type))
{
}

mk::stdlib::heap_type_erased_t& mk::stdlib::heap_type_erased_t::operator=(mk::stdlib::heap_type_erased_t const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_heap = other.m_heap;
	m_type = other.m_type;
	return *this;
}

mk::stdlib::heap_type_erased_t& mk::stdlib::heap_type_erased_t::operator=(mk::stdlib::heap_type_erased_t&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_heap = mk::stdlib::move(other.m_heap);
	m_type = mk::stdlib::move(other.m_type);
	return *this;
}

mk::stdlib::heap_type_erased_t::~heap_type_erased_t() noexcept
{
}

void mk::stdlib::heap_type_erased_t::swap(mk::stdlib::heap_type_erased_t& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_heap, other.m_heap);
	swap(m_type, other.m_type);
}

[[nodiscard]] mk::stdlib::heap_type_erased_t::operator bool() const noexcept
{
	return !!m_heap;
}


[[nodiscard]] void* const& mk::stdlib::heap_type_erased_t::get_heap() const noexcept
{
	return m_heap;
}

[[nodiscard]] int const& mk::stdlib::heap_type_erased_t::get_type() const noexcept
{
	return m_type;
}


[[nodiscard]] void* mk::stdlib::heap_type_erased_t::alloc(mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_type_erased_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_type_erased_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::virtuall:
		{
			typedef mk::stdlib::heap_virtual_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.alloc(bytes);
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
	return ret;
}

[[nodiscard]] mk::stdlib::size_t mk::stdlib::heap_type_erased_t::size(void const* const& mem) const noexcept
{
	MK_STDLIB_ASSERT(*this);
	mk::stdlib::size_t ret;
	switch(static_cast<mk::stdlib::impl::heap_type_erased_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_type_erased_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::virtuall:
		{
			typedef mk::stdlib::heap_virtual_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.size(mem);
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
	return ret;
}

[[nodiscard]] void* mk::stdlib::heap_type_erased_t::realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_type_erased_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_type_erased_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::virtuall:
		{
			typedef mk::stdlib::heap_virtual_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc(mem, bytes);
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
	return ret;
}

[[nodiscard]] void* mk::stdlib::heap_type_erased_t::realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_type_erased_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_type_erased_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::virtuall:
		{
			typedef mk::stdlib::heap_virtual_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
	return ret;
}

void mk::stdlib::heap_type_erased_t::free(void const* const& mem) noexcept
{
	MK_STDLIB_ASSERT(*this);
	switch(static_cast<mk::stdlib::impl::heap_type_erased_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_type_erased_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_type_erased_type_t::virtuall:
		{
			typedef mk::stdlib::heap_virtual_t concrete_t;
			concrete_t& heap = *static_cast<concrete_t*>(m_heap);
			heap.free(mem);
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
}

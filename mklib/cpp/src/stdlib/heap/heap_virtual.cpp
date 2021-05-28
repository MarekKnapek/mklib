#include "heap_virtual.hpp"

#include "../algorithm/max.hpp"
#include "../assert.hpp"
#include "../macros.hpp"
#include "../new.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"
#include "heap_multi_threaded.hpp"
#include "heap_process.hpp"
#include "heap_single_threaded.hpp"
#include "heap_type_erased.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			enum class heap_virtual_type_t : int
			{
				none,
				multi_threaded,
				process,
				single_threaded,
				type_erased,
			};
			template<typename>
			struct heap_virtual_type_to_enum_t
			{
			};
			template<>
			struct heap_virtual_type_to_enum_t<mk::stdlib::heap_multi_threaded_t>
			{
				static constexpr mk::stdlib::impl::heap_virtual_type_t s_value = mk::stdlib::impl::heap_virtual_type_t::multi_threaded;
			};
			template<>
			struct heap_virtual_type_to_enum_t<mk::stdlib::heap_process_t>
			{
				static constexpr mk::stdlib::impl::heap_virtual_type_t s_value = mk::stdlib::impl::heap_virtual_type_t::process;
			};
			template<>
			struct heap_virtual_type_to_enum_t<mk::stdlib::heap_single_threaded_t>
			{
				static constexpr mk::stdlib::impl::heap_virtual_type_t s_value = mk::stdlib::impl::heap_virtual_type_t::single_threaded;
			};
			template<>
			struct heap_virtual_type_to_enum_t<mk::stdlib::heap_type_erased_t>
			{
				static constexpr mk::stdlib::impl::heap_virtual_type_t s_value = mk::stdlib::impl::heap_virtual_type_t::type_erased;
			};
		}
	}
}


mk::stdlib::heap_virtual_t::heap_virtual_t() noexcept :
	m_type(),
	m_storage()
{
}

template<typename t>
[[nodiscard]] mk::stdlib::heap_virtual_t mk::stdlib::heap_virtual_t::make() noexcept
{
	static constexpr auto const s_max_size = mk::stdlib::max
	(
		sizeof(mk::stdlib::heap_multi_threaded_t),
		sizeof(mk::stdlib::heap_process_t),
		sizeof(mk::stdlib::heap_single_threaded_t),
		sizeof(mk::stdlib::heap_type_erased_t)
	);
	static constexpr auto const s_max_align = mk::stdlib::max
	(
		alignof(mk::stdlib::heap_multi_threaded_t),
		alignof(mk::stdlib::heap_process_t),
		alignof(mk::stdlib::heap_single_threaded_t),
		alignof(mk::stdlib::heap_type_erased_t)
	);
	static_assert(sizeof(mk::stdlib::heap_virtual_t::m_storage) == s_max_size);
	static_assert(alignof(decltype(mk::stdlib::heap_virtual_t::m_storage)) == s_max_align);

	mk::stdlib::heap_virtual_t ret;
	ret.m_type = static_cast<int>(mk::stdlib::impl::heap_virtual_type_to_enum_t<t>::s_value);
	new(static_cast<void*>(&ret.m_storage), mk::stdlib::new_t{})t();
	return ret;
}

mk::stdlib::heap_virtual_t::heap_virtual_t(mk::stdlib::heap_virtual_t&& other) noexcept :
	mk::stdlib::heap_virtual_t()
{
	this->operator=(mk::stdlib::move(other));
}

mk::stdlib::heap_virtual_t& mk::stdlib::heap_virtual_t::operator=(mk::stdlib::heap_virtual_t&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	destroy();
	m_type = other.m_type;
	other.m_type = static_cast<int>(mk::stdlib::impl::heap_virtual_type_t::none);
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::none:
		{
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&other.m_storage);
			new(&m_storage, mk::stdlib::new_t{})concrete_t(mk::stdlib::move(heap));
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&other.m_storage);
			new(&m_storage, mk::stdlib::new_t{})concrete_t(mk::stdlib::move(heap));
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&other.m_storage);
			new(&m_storage, mk::stdlib::new_t{})concrete_t(mk::stdlib::move(heap));
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&other.m_storage);
			new(&m_storage, mk::stdlib::new_t{})concrete_t(mk::stdlib::move(heap));
		}
		break;
		default:
		{
			MK_STDLIB_ASSERT(false);
			MK_STDLIB_UNREACHABLE();
		}
		break;
	}
	return *this;
}

mk::stdlib::heap_virtual_t::~heap_virtual_t() noexcept
{
	destroy();
}

mk::stdlib::heap_virtual_t::operator bool() const noexcept
{
	return !!m_type;
}

void mk::stdlib::heap_virtual_t::swap(mk::stdlib::heap_virtual_t& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);

	using mk::stdlib::swap;

	mk::stdlib::heap_virtual_t tmp = mk::stdlib::move(*this);
	*this = mk::stdlib::move(other);
	other = mk::stdlib::move(tmp);
}


void mk::stdlib::heap_virtual_t::destroy() noexcept
{
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::none:
		{
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.~concrete_t();
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.~concrete_t();
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.~concrete_t();
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.~concrete_t();
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


[[nodiscard]] void* mk::stdlib::heap_virtual_t::alloc(mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.alloc(bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
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

[[nodiscard]] mk::stdlib::size_t mk::stdlib::heap_virtual_t::size(void const* const& mem) const noexcept
{
	MK_STDLIB_ASSERT(*this);
	mk::stdlib::size_t ret;
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t const& heap = *reinterpret_cast<concrete_t const*>(&m_storage);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t const& heap = *reinterpret_cast<concrete_t const*>(&m_storage);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t const& heap = *reinterpret_cast<concrete_t const*>(&m_storage);
			ret = heap.size(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t const& heap = *reinterpret_cast<concrete_t const*>(&m_storage);
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

[[nodiscard]] void* mk::stdlib::heap_virtual_t::realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
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

[[nodiscard]] void* mk::stdlib::heap_virtual_t::realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	MK_STDLIB_ASSERT(*this);
	void* ret;
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			ret = heap.realloc_inplace(mem, bytes);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
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

void mk::stdlib::heap_virtual_t::free(void const* const& mem) noexcept
{
	MK_STDLIB_ASSERT(*this);
	switch(static_cast<mk::stdlib::impl::heap_virtual_type_t>(m_type))
	{
		case mk::stdlib::impl::heap_virtual_type_t::multi_threaded:
		{
			typedef mk::stdlib::heap_multi_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::process:
		{
			typedef mk::stdlib::heap_process_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::single_threaded:
		{
			typedef mk::stdlib::heap_single_threaded_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
			heap.free(mem);
		}
		break;
		case mk::stdlib::impl::heap_virtual_type_t::type_erased:
		{
			typedef mk::stdlib::heap_type_erased_t concrete_t;
			concrete_t& heap = *reinterpret_cast<concrete_t*>(&m_storage);
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


template mk::stdlib::heap_virtual_t mk::stdlib::heap_virtual_t::make<mk::stdlib::heap_multi_threaded_t>() noexcept;
template mk::stdlib::heap_virtual_t mk::stdlib::heap_virtual_t::make<mk::stdlib::heap_process_t>() noexcept;
template mk::stdlib::heap_virtual_t mk::stdlib::heap_virtual_t::make<mk::stdlib::heap_single_threaded_t>() noexcept;
template mk::stdlib::heap_virtual_t mk::stdlib::heap_virtual_t::make<mk::stdlib::heap_type_erased_t>() noexcept;

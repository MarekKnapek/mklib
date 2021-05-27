#include "unique_ptr_multi.hpp"

#include "../assert.hpp" // MK_STDLIB_ASSERT
#include "../cstdlib.hpp" // mk::stdlib::malloc
#include "../ints.hpp" // mk::stdlib::uintptr_t
#include "../memory.hpp" // mk::stdlib::uninitialized_default_construct_n
#include "../size.hpp" // mk::stdlib::size_t
#include "../type_traits/is_trivial.hpp" // mk::stdlib::is_trivial_t
#include "../type_traits/remove_extent.hpp" // mk::stdlib::remove_extent_t
#include "../utility/swap.hpp" // mk::stdlib::swap


template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t() noexcept :
	m_ptr()
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t(t* const& ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept :
	mk::stdlib::unique_ptr_t<t[], d>()
{
	swap(other);
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>& mk::stdlib::unique_ptr_t<t[], d>::operator=(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::~unique_ptr_t() noexcept
{
	if(m_ptr == nullptr)
	{
		return;
	}
	d{}(m_ptr);
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t[], d>::swap(mk::stdlib::unique_ptr_t<t[], d>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_ptr, other.m_ptr);
}


template<typename t, typename d>
[[nodiscard]] t* const& mk::stdlib::unique_ptr_t<t[], d>::get() const noexcept
{
	return m_ptr;
}

template<typename t, typename d>
[[nodiscard]] mk::stdlib::unique_ptr_t<t[], d>::operator bool() const noexcept
{
	return m_ptr != nullptr;
}

template<typename t, typename d>
[[nodiscard]] t& mk::stdlib::unique_ptr_t<t[], d>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(m_ptr != nullptr);
	return m_ptr[idx];
}


template<typename t, typename d>
[[nodiscard]] t* mk::stdlib::unique_ptr_t<t[], d>::release() noexcept
{
	t* const ptr = m_ptr;
	m_ptr = nullptr;
	return ptr;
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t[], d>::reset(t* const& ptr) noexcept
{
	MK_STDLIB_ASSERT((m_ptr == nullptr) || (m_ptr != ptr));
	mk::stdlib::unique_ptr_t<t[], d> new_up{ptr};
	swap(new_up);
}


template<typename t>
mk::stdlib::unique_ptr_t<t> mk::stdlib::make_unique(mk::stdlib::size_t const& count) noexcept
{
	typedef mk::stdlib::remove_extent_t<t>::type_t non_array_t;
	if constexpr(mk::stdlib::is_trivial_t<non_array_t>::s_value)
	{
		non_array_t* const arr = static_cast<non_array_t*>(mk::stdlib::malloc(count * sizeof(non_array_t)));
		return mk::stdlib::unique_ptr_t<t>{arr};
	}
	else
	{
		void* const mem = mk::stdlib::malloc(sizeof(mk::stdlib::size_t) + count * sizeof(non_array_t));
		mk::stdlib::size_t& arr_count = *static_cast<mk::stdlib::size_t*>(mem);
		arr_count = count;
		non_array_t* const arr = reinterpret_cast<non_array_t*>(reinterpret_cast<mk::stdlib::uintptr_t>(mem) + sizeof(mk::stdlib::size_t));
		mk::stdlib::uninitialized_default_construct_n(arr, count);
		return mk::stdlib::unique_ptr_t<t>{arr};
	}
}

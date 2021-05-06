#include "array.hpp"

#include "assert.hpp"
#include "utility/swap.hpp"


template<typename t, mk::stdlib::size_t n>
constexpr void mk::stdlib::array_t<t, n>::swap(mk::stdlib::array_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	for(mk::stdlib::size_t i = 0; i != n; ++i)
	{
		swap(m_array[i], other.m_array[i]);
	}
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::array_t<t, n>::size() const noexcept
{
	return n;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::cbegin() const noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::begin() const noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::cend() const noexcept
{
	return m_array + n;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::end() const noexcept
{
	return m_array + n;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::cdata() const noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const* mk::stdlib::array_t<t, n>::data() const noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::array_t<t, n>::cfront() const noexcept
{
	return m_array[0];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::array_t<t, n>::front() const noexcept
{
	return m_array[0];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::array_t<t, n>::cback() const noexcept
{
	return m_array[n];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::array_t<t, n>::back() const noexcept
{
	return m_array[n];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::array_t<t, n>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(idx < n);
	return m_array[idx];
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t* mk::stdlib::array_t<t, n>::begin() noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t* mk::stdlib::array_t<t, n>::end() noexcept
{
	return m_array + n;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t* mk::stdlib::array_t<t, n>::data() noexcept
{
	return m_array;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t& mk::stdlib::array_t<t, n>::front() noexcept
{
	return m_array[0];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t& mk::stdlib::array_t<t, n>::back() noexcept
{
	return m_array[n];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t& mk::stdlib::array_t<t, n>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	MK_STDLIB_ASSERT(idx < n);
	return m_array;
}

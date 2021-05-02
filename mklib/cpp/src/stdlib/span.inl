#include "span.hpp"

#include "assert.hpp"
#include "utility/swap.hpp"


template<typename t>
constexpr mk::stdlib::span_t<t>::span_t() noexcept :
	m_data(),
	m_size()
{
}

template<typename t>
constexpr mk::stdlib::span_t<t>::span_t(t* const& data, mk::stdlib::size_t const& size) noexcept :
	m_data(data),
	m_size(size)
{
}

template<typename t>
constexpr mk::stdlib::span_t<t>::span_t(t* const& begin, t const* const& end) noexcept :
	m_data(begin),
	m_size(end - begin)
{
	MK_STDLIB_ASSERT(end >= begin);
}

template<typename t>
template<mk::stdlib::size_t n>
constexpr mk::stdlib::span_t<t>::span_t(t(&arr)[n]) noexcept :
	m_data(arr),
	m_size(n)
{
}

template<typename t>
constexpr mk::stdlib::span_t<t>::span_t(mk::stdlib::span_t<t> const& other) noexcept :
	m_data(other.m_data),
	m_size(other.m_size)
{
}

template<typename t>
constexpr mk::stdlib::span_t<t>::span_t(mk::stdlib::span_t<t>&& other) noexcept :
	m_data(other.m_data),
	m_size(other.m_size)
{
}

template<typename t>
constexpr mk::stdlib::span_t<t>& mk::stdlib::span_t<t>::operator=(mk::stdlib::span_t<t> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_data = other.m_data;
	m_size = other.m_data;
	return *this;
}

template<typename t>
constexpr mk::stdlib::span_t<t>& mk::stdlib::span_t<t>::operator=(mk::stdlib::span_t<t>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_data = other.m_data;
	m_size = other.m_data;
	return *this;
}

template<typename t>
constexpr mk::stdlib::span_t<t>::~span_t() noexcept
{
}

template<typename t>
constexpr void mk::stdlib::span_t<t>::swap(mk::stdlib::span_t<t>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_data, other.m_data);
	swap(m_size, other.m_size);
}


template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::cdata() const noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::data() const noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::span_t<t>::size() const noexcept
{
	return m_size;
}

template<typename t>
[[nodiscard]] constexpr bool mk::stdlib::span_t<t>::empty() const noexcept
{
	return m_size == 0;
}

template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::cbegin() const noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::begin() const noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::cend() const noexcept
{
	return m_data + m_size;
}

template<typename t>
[[nodiscard]] constexpr t const* mk::stdlib::span_t<t>::end() const noexcept
{
	return m_data + m_size;
}

template<typename t>
[[nodiscard]] constexpr t const& mk::stdlib::span_t<t>::cfront() const noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[0];
}

template<typename t>
[[nodiscard]] constexpr t const& mk::stdlib::span_t<t>::front() const noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[0];
}

template<typename t>
[[nodiscard]] constexpr t const& mk::stdlib::span_t<t>::cback() const noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[m_size - 1];
}
template<typename t>
[[nodiscard]] constexpr t const& mk::stdlib::span_t<t>::back() const noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[m_size - 1];
}

template<typename t>
[[nodiscard]] constexpr t const& mk::stdlib::span_t<t>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(idx < m_size);
	return m_data[idx];
}

template<typename t>
[[nodiscard]] constexpr mk::stdlib::span_t<t> mk::stdlib::span_t<t>::first(mk::stdlib::size_t const& count) const noexcept
{
	MK_STDLIB_ASSERT(count <= m_size);
	return mk::stdlib::span_t<t>{m_data, count};
}

template<typename t>
[[nodiscard]] constexpr mk::stdlib::span_t<t> mk::stdlib::span_t<t>::last(mk::stdlib::size_t const& count) const noexcept
{
	MK_STDLIB_ASSERT(count <= m_size);
	return mk::stdlib::span_t<t>{m_data + (m_size - count), count};
}

template<typename t>
[[nodiscard]] constexpr mk::stdlib::span_t<t> mk::stdlib::span_t<t>::sub_span(mk::stdlib::size_t const& offset, mk::stdlib::size_t const& count) const noexcept
{
	MK_STDLIB_ASSERT(offset <= m_size);
	MK_STDLIB_ASSERT(count <= m_size - offset);
	return mk::stdlib::span_t<t>{m_data + offset, count};
}

template<typename t>
[[nodiscard]] constexpr mk::stdlib::span_t<t const> mk::stdlib::span_t<t>::as_const() const noexcept
{
	return mk::stdlib::span_t<t const>{m_data, m_size};
}


template<typename t>
[[nodiscard]] constexpr t* mk::stdlib::span_t<t>::data() noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr t* mk::stdlib::span_t<t>::begin() noexcept
{
	return m_data;
}

template<typename t>
[[nodiscard]] constexpr t* mk::stdlib::span_t<t>::end() noexcept
{
	return m_data + m_size;
}

template<typename t>
[[nodiscard]] constexpr t& mk::stdlib::span_t<t>::front() noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[0];
}

template<typename t>
[[nodiscard]] constexpr t& mk::stdlib::span_t<t>::back() noexcept
{
	MK_STDLIB_ASSERT(m_size != 0);
	return m_data[m_size - 1];
}

template<typename t>
[[nodiscard]] constexpr t& mk::stdlib::span_t<t>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	MK_STDLIB_ASSERT(idx < m_size);
	return m_data[idx];
}

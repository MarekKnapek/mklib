#include "ring_buffer_iterator.hpp"

#include "utility/move.hpp" // mk::stdlib::move
#include "assert.hpp" // MK_STDLIB_ASSERT
#include "utility/swap.hpp" // mk::stdlib::swap


template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>::ring_buffer_iterator_t() noexcept :
	m_ring_buffer(),
	m_idx()
{
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>::ring_buffer_iterator_t(mk::stdlib::ring_buffer_t<t, n>* const& ring_buffer, mk::stdlib::size_t const& idx) noexcept :
	m_ring_buffer(ring_buffer),
	m_idx(idx)
{
	MK_STDLIB_ASSERT
	(
		((m_ring_buffer == nullptr) && (m_idx == 0)) ||
		((m_ring_buffer != nullptr) && ((m_idx == s_minus_one) || (m_idx <= m_ring_buffer->size())))
	);
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>::ring_buffer_iterator_t(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) noexcept :
	m_ring_buffer(other.m_ring_buffer),
	m_idx(other.m_idx)
{
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>::ring_buffer_iterator_t(mk::stdlib::ring_buffer_iterator_t<t, n>&& other) noexcept :
	m_ring_buffer(mk::stdlib::move(other.m_ring_buffer)),
	m_idx(mk::stdlib::move(other.m_idx))
{
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator=(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) noexcept
{
	m_ring_buffer = other.m_ring_buffer;
	m_idx = other.m_idx;
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator=(mk::stdlib::ring_buffer_iterator_t<t, n>&& other) noexcept
{
	m_ring_buffer = mk::stdlib::move(other.m_ring_buffer);
	m_idx = mk::stdlib::move(other.m_idx);
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>::~ring_buffer_iterator_t() noexcept
{
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_iterator_t<t, n>::swap(mk::stdlib::ring_buffer_iterator_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_ring_buffer, other.m_ring_buffer);
	swap(m_idx, other.m_idx);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_t<t, n>* const& mk::stdlib::ring_buffer_iterator_t<t, n>::get_ring_buffer() const noexcept
{
	return m_ring_buffer;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::size_t const& mk::stdlib::ring_buffer_iterator_t<t, n>::get_idx() const noexcept
{
	return m_idx;
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator==(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	return
		m_ring_buffer == other.m_ring_buffer &&
		m_idx == other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator!=(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	return !operator==(other);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator<(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer == other.m_ring_buffer);
	return m_idx < other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator>(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer == other.m_ring_buffer);
	return m_idx > other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator<=(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer == other.m_ring_buffer);
	return m_idx <= other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_iterator_t<t, n>::operator>=(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer == other.m_ring_buffer);
	return m_idx >= other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_iterator_t<t, n>::operator+(mk::stdlib::ptrdiff_t const& amount) const noexcept
{
	mk::stdlib::ring_buffer_iterator_t<t, n> copy = *this;
	return copy += amount;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_iterator_t<t, n>::operator-(mk::stdlib::ptrdiff_t const& amount) const noexcept
{
	return operator+(-amount);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ptrdiff_t mk::stdlib::ring_buffer_iterator_t<t, n>::operator-(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) const noexcept
{
	return m_idx - other.m_idx;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t& mk::stdlib::ring_buffer_iterator_t<t, n>::operator*() const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer);
	return (*m_ring_buffer)[m_idx];
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t& mk::stdlib::ring_buffer_iterator_t<t, n>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer);
	return (*m_ring_buffer)[m_idx + idx];
}


template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator++() noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer);
	MK_STDLIB_ASSERT(m_idx != m_ring_buffer->size());
	++m_idx;
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator--() noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer);
	MK_STDLIB_ASSERT(m_idx != s_minus_one);
	--m_idx;
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_iterator_t<t, n>::operator++(int) noexcept
{
	mk::stdlib::ring_buffer_iterator_t<t, n> copy = *this;
	operator++();
	return copy;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_iterator_t<t, n>::operator--(int) noexcept
{
	mk::stdlib::ring_buffer_iterator_t<t, n> copy = *this;
	operator--();
	return copy;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator+=(mk::stdlib::ptrdiff_t const& amount) noexcept
{
	MK_STDLIB_ASSERT(m_ring_buffer);
	MK_STDLIB_ASSERT(((m_idx + amount) == s_minus_one) || ((m_idx + amount) <= m_ring_buffer->size()));
	m_idx += amount;
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_iterator_t<t, n>& mk::stdlib::ring_buffer_iterator_t<t, n>::operator-=(mk::stdlib::ptrdiff_t const& amount) noexcept
{
	return operator+=(-amount);
}

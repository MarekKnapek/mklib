#include "ring_buffer.hpp"

#include "assert.hpp"
#include "utility/move.hpp"
#include "utility/swap.hpp"
#include "algorithm/min.hpp"
#include "memory.hpp"


template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t() noexcept :
	/*m_array(),*/ /* no need to initialize */
	m_read(),
	m_write()
{
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept :
	mk::stdlib::ring_buffer_t<t, n>()
{
	auto const first_h = other.first_half();
	auto const second_h = other.second_half();
	t* const first_ptr = reinterpret_cast<t*>(m_array.data());
	t* const second_ptr = first_ptr + first_h.size();
	mk::stdlib::uninitialized_copy(first_h.cbegin(), first_h.cend(), first_ptr);
	mk::stdlib::uninitialized_copy(second_h.cbegin(), second_h.cend(), second_ptr);
	m_write += first_h.size() + second_h.size();
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept :
	mk::stdlib::ring_buffer_t<t, n>()
{
	auto first_h = other.first_half();
	auto second_h = other.second_half();
	t* const first_ptr = reinterpret_cast<t*>(m_array.data());
	t* const second_ptr = first_ptr + first_h.size();
	mk::stdlib::uninitialized_move(first_h.begin(), first_h.end(), first_ptr);
	mk::stdlib::uninitialized_move(second_h.begin(), second_h.end(), second_ptr);
	m_write += first_h.size() + second_h.size();
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>& mk::stdlib::ring_buffer_t<t, n>::operator=(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	// TODO
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>& mk::stdlib::ring_buffer_t<t, n>::operator=(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	// TODO
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::~ring_buffer_t() noexcept
{
	auto const first_h = first_half();
	auto const second_h = second_half();
	mk::stdlib::destroy_n(first_h.data(), first_h.size());
	mk::stdlib::destroy_n(second_h.data(), second_h.size());
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::swap(mk::stdlib::ring_buffer_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	// TODO
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr bool mk::stdlib::ring_buffer_t<t, n>::empty() const noexcept
{
	return m_write == m_read;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr bool mk::stdlib::ring_buffer_t<t, n>::full() const noexcept
{
	return m_write == m_read + s_capacity;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::size() const noexcept
{
	return m_write - m_read;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::capacity() const noexcept
{
	return s_capacity;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::free() const noexcept
{
	return capacity() - size();
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::span_t<t const> mk::stdlib::ring_buffer_t<t, n>::first_half() const noexcept
{
	t const* const ptr = reinterpret_cast<t const*>(m_array.data()) + (m_read & s_mask);
	mk::stdlib::size_t const count = mk::stdlib::min(s_capacity - (m_read & s_mask), m_write - m_read);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::span_t<t const> mk::stdlib::ring_buffer_t<t, n>::second_half() const noexcept
{
	t const* const ptr = reinterpret_cast<t const*>(m_array.data());
	mk::stdlib::size_t const count = (m_write & s_mask) < (m_read & s_mask) ? (m_write & s_mask) : static_cast<mk::stdlib::size_t>(0);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t const& mk::stdlib::ring_buffer_t<t, n>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(idx < size());
	t const* ptr = reinterpret_cast<t const*>(m_array.data()) + ((m_read + idx) & s_mask);
	return *ptr;
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::span_t<t> mk::stdlib::ring_buffer_t<t, n>::first_half() noexcept
{
	t* const ptr = reinterpret_cast<t*>(m_array.data()) + (m_read & s_mask);
	mk::stdlib::size_t const count = mk::stdlib::min(s_capacity - (m_read & s_mask), m_write - m_read);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr mk::stdlib::span_t<t> mk::stdlib::ring_buffer_t<t, n>::second_half() noexcept
{
	t* const ptr = reinterpret_cast<t*>(m_array.data());
	mk::stdlib::size_t const count = (m_write & s_mask) < (m_read & s_mask) ? (m_write & s_mask) : static_cast<mk::stdlib::size_t>(0);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] constexpr t& mk::stdlib::ring_buffer_t<t, n>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	MK_STDLIB_ASSERT(idx < size());
	t* ptr = reinterpret_cast<t*>(m_array.data()) + ((m_read + idx) & s_mask);
	return *ptr;
}

template<typename t, mk::stdlib::size_t n>
template<typename u>
constexpr t& mk::stdlib::ring_buffer_t<t, n>::push_back(u&& obj) noexcept
{
	MK_STDLIB_ASSERT(!full());
	t* const ptr = reinterpret_cast<t*>(m_array.data()) + (m_write & s_mask);
	mk::stdlib::construct_at(ptr, obj);
	++m_write;
	return *ptr;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::pop_front() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	t* const ptr = reinterpret_cast<t*>(m_array.data()) + (m_read & s_mask);
	mk::stdlib::destroy_at(ptr);
	++m_read;
}

#include "ring_buffer.hpp"

#include "../runtime/asan.hpp"
#include "algorithm/min.hpp" // mk::stdlib::min
#include "assert.hpp" // MK_STDLIB_ASSERT
#include "memory.hpp" // mk::stdlib::uninitialized_copy, mk::stdlib::uninitialized_move, mk::stdlib::construct_at, mk::stdlib::destroy_n
#include "ring_buffer_const_iterator.hpp" // mk::stdlib::ring_buffer_const_iterator_t
#include "ring_buffer_iterator.hpp" // mk::stdlib::ring_buffer_iterator_t
#include "utility/forward.hpp" // mk::stdlib::forward
#include "utility/move.hpp" // mk::stdlib::move
#include "utility/swap.hpp" // mk::stdlib::swap


template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t() noexcept :
	/*m_array(),*/ /* no need to initialize */
	m_read(),
	m_write()
{
	mk::runtime::asan_poison_memory_region(&m_array, sizeof(m_array));
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept :
	mk::stdlib::ring_buffer_t<t, n>()
{
	mk::stdlib::span_t<t const> const other_fh = other.first_half();
	mk::stdlib::span_t<t const> const other_sh = other.second_half();
	t* const self_first_ptr = data();
	t* const self_second_ptr = self_first_ptr + other_fh.size();
	mk::stdlib::uninitialized_copy(other_fh.cbegin(), other_fh.cend(), self_first_ptr);
	mk::stdlib::uninitialized_copy(other_sh.cbegin(), other_sh.cend(), self_second_ptr);
	m_write = other_fh.size() + other_sh.size();
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::ring_buffer_t(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept :
	mk::stdlib::ring_buffer_t<t, n>()
{
	mk::stdlib::span_t<t> other_fh = other.first_half();
	mk::stdlib::span_t<t> other_sh = other.second_half();
	t* const self_first_ptr = data();
	t* const self_second_ptr = self_first_ptr + other_fh.size();
	mk::stdlib::uninitialized_move(other_fh.begin(), other_fh.end(), self_first_ptr);
	mk::stdlib::uninitialized_move(other_sh.begin(), other_sh.end(), self_second_ptr);
	m_write = other_fh.size() + other_sh.size();
	other.clear();
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>& mk::stdlib::ring_buffer_t<t, n>::operator=(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	mk::stdlib::size_t const my_size = size();
	mk::stdlib::size_t const other_size = other.size();
	if(my_size < other_size)
	{
		for(mk::stdlib::size_t i = 0; i != my_size; ++i)
		{
			operator[](i) = other[i];
		}
		mk::stdlib::size_t const diff = other_size - my_size;
		for(mk::stdlib::size_t i = 0; i != diff; ++i)
		{
			push_back(other[my_size + i]);
		}
	}
	else
	{
		for(mk::stdlib::size_t i = 0; i != other_size; ++i)
		{
			operator[](i) = other[i];
		}
		mk::stdlib::size_t const diff = my_size - other_size;
		pop_back(diff);
	}
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>& mk::stdlib::ring_buffer_t<t, n>::operator=(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	mk::stdlib::size_t const my_size = size();
	mk::stdlib::size_t const other_size = other.size();
	if(my_size < other_size)
	{
		for(mk::stdlib::size_t i = 0; i != my_size; ++i)
		{
			operator[](i) = mk::stdlib::move(other[i]);
		}
		mk::stdlib::size_t const diff = other_size - my_size;
		for(mk::stdlib::size_t i = 0; i != diff; ++i)
		{
			push_back(mk::stdlib::move(other[my_size + i]));
		}
	}
	else
	{
		for(mk::stdlib::size_t i = 0; i != other_size; ++i)
		{
			operator[](i) = mk::stdlib::move(other[i]);
		}
		mk::stdlib::size_t const diff = my_size - other_size;
		pop_back(diff);
	}
	other.clear();
	return *this;
}

template<typename t, mk::stdlib::size_t n>
mk::stdlib::ring_buffer_t<t, n>::~ring_buffer_t() noexcept
{
	mk::stdlib::span_t<t> const fh = first_half();
	mk::stdlib::span_t<t> const sh = second_half();
	mk::stdlib::destroy_n(fh.data(), fh.size());
	mk::stdlib::destroy_n(sh.data(), sh.size());
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::swap(mk::stdlib::ring_buffer_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	mk::stdlib::size_t const my_size = size();
	mk::stdlib::size_t const other_size = other.size();
	if(my_size < other_size)
	{
		for(mk::stdlib::size_t i = 0; i != my_size; ++i)
		{
			swap(operator[](i), other[i]);
		}
		mk::stdlib::size_t const diff = other_size - my_size;
		for(mk::stdlib::size_t i = 0; i != diff; ++i)
		{
			push_back(mk::stdlib::move(other[my_size + i]));
		}
		other.pop_back(diff);
	}
	else
	{
		for(mk::stdlib::size_t i = 0; i != other_size; ++i)
		{
			swap(operator[](i), other[i]);
		}
		mk::stdlib::size_t const diff = my_size - other_size;
		for(mk::stdlib::size_t i = 0; i != diff; ++i)
		{
			other.push_back(mk::stdlib::move(operator[](other_size + i)));
		}
		pop_back(diff);
	}
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_t<t, n>::empty() const noexcept
{
	return m_write == m_read;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] bool mk::stdlib::ring_buffer_t<t, n>::full() const noexcept
{
	return m_write == m_read + s_capacity;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::size() const noexcept
{
	return m_write - m_read;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::capacity() const noexcept
{
	return s_capacity;
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::ring_buffer_t<t, n>::free() const noexcept
{
	return capacity() - size();
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::span_t<t const> mk::stdlib::ring_buffer_t<t, n>::first_half() const noexcept
{
	t const* const ptr = data() + (m_read & s_mask);
	mk::stdlib::size_t const count = mk::stdlib::min(s_capacity - (m_read & s_mask), m_write - m_read);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::span_t<t const> mk::stdlib::ring_buffer_t<t, n>::second_half() const noexcept
{
	t const* const ptr = data();
	mk::stdlib::size_t const count = (m_write & s_mask) < (m_read & s_mask) ? (m_write & s_mask) : static_cast<mk::stdlib::size_t>(0);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t const& mk::stdlib::ring_buffer_t<t, n>::cfront() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](0);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t const& mk::stdlib::ring_buffer_t<t, n>::cback() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](size() - 1);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t const& mk::stdlib::ring_buffer_t<t, n>::front() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](0);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t const& mk::stdlib::ring_buffer_t<t, n>::back() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](size() - 1);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::cbegin() const noexcept
{
	return {this, 0};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::cend() const noexcept
{
	return {this, size()};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::begin() const noexcept
{
	return {this, 0};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::end() const noexcept
{
	return {this, size()};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t const& mk::stdlib::ring_buffer_t<t, n>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(idx < size());
	t const* ptr = data() + ((m_read + idx) & s_mask);
	return *ptr;
}


template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::span_t<t> mk::stdlib::ring_buffer_t<t, n>::first_half() noexcept
{
	t* const ptr = data() + (m_read & s_mask);
	mk::stdlib::size_t const count = mk::stdlib::min(s_capacity - (m_read & s_mask), m_write - m_read);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::span_t<t> mk::stdlib::ring_buffer_t<t, n>::second_half() noexcept
{
	t* const ptr = data();
	mk::stdlib::size_t const count = (m_write & s_mask) < (m_read & s_mask) ? (m_write & s_mask) : static_cast<mk::stdlib::size_t>(0);
	return {ptr, count};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t& mk::stdlib::ring_buffer_t<t, n>::front() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](0);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t& mk::stdlib::ring_buffer_t<t, n>::back() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	return operator[](size() - 1);
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::begin() noexcept
{
	return {this, 0};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] mk::stdlib::ring_buffer_iterator_t<t, n> mk::stdlib::ring_buffer_t<t, n>::end() noexcept
{
	return {this, size()};
}

template<typename t, mk::stdlib::size_t n>
[[nodiscard]] t& mk::stdlib::ring_buffer_t<t, n>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	MK_STDLIB_ASSERT(idx < size());
	t* ptr = data() + ((m_read + idx) & s_mask);
	return *ptr;
}

template<typename t, mk::stdlib::size_t n>
template<typename u>
t& mk::stdlib::ring_buffer_t<t, n>::push_back(u&& obj) noexcept
{
	MK_STDLIB_ASSERT(!full());
	t* const ptr = data() + (m_write & s_mask);
	mk::stdlib::construct_at(ptr, mk::stdlib::forward<u>(obj));
	++m_write;
	return *ptr;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::pop_back() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	t* const ptr = data() + ((m_write - 1) & s_mask);
	mk::stdlib::destroy_at(ptr);
	--m_write;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::pop_back(mk::stdlib::size_t const& count) noexcept
{
	MK_STDLIB_ASSERT(count <= size());

	mk::stdlib::span_t<t> const sh = second_half();
	mk::stdlib::size_t const sh_count = mk::stdlib::min(sh.size(), static_cast<mk::stdlib::size_t>(count));
	mk::stdlib::destroy_n(sh.end() - sh_count, sh_count);

	mk::stdlib::span_t<t> const fh = first_half();
	mk::stdlib::size_t const fh_count = count - sh_count;
	mk::stdlib::destroy_n(fh.end() - fh_count, fh_count);

	m_write -= count;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::pop_front() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	t* const ptr = data() + (m_read & s_mask);
	mk::stdlib::destroy_at(ptr);
	++m_read;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::pop_front(mk::stdlib::size_t const& count) noexcept
{
	MK_STDLIB_ASSERT(count <= size());

	mk::stdlib::span_t<t> const fh = first_half();
	mk::stdlib::size_t const fh_count = mk::stdlib::min(fh.size(), static_cast<mk::stdlib::size_t>(count));
	mk::stdlib::destroy_n(fh.begin() + fh_count, fh_count);

	mk::stdlib::span_t<t> const sh = second_half();
	mk::stdlib::size_t const sh_count = count - fh_count;
	mk::stdlib::destroy_n(sh.begin() - sh_count, sh_count);

	m_read += count;
}

template<typename t, mk::stdlib::size_t n>
void mk::stdlib::ring_buffer_t<t, n>::clear() noexcept
{
	mk::stdlib::span_t<t> const fh = first_half();
	mk::stdlib::span_t<t> const sh = second_half();
	mk::stdlib::destroy_n(fh.data(), fh.size());
	mk::stdlib::destroy_n(sh.data(), sh.size());
	m_read = m_write;
}


template<typename t, mk::stdlib::size_t n>
t const* mk::stdlib::ring_buffer_t<t, n>::data() const noexcept
{
	return static_cast<t const*>(static_cast<void const*>(m_array.data()->m_data));
}

template<typename t, mk::stdlib::size_t n>
t* mk::stdlib::ring_buffer_t<t, n>::data() noexcept
{
	return static_cast<t*>(static_cast<void*>(m_array.data()->m_data));
}

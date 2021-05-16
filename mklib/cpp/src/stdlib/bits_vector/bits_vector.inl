#include "bits_vector.hpp"

#include "../algorithm/copy.hpp"
#include "../algorithm/fill.hpp"
#include "../algorithm/max.hpp"
#include "../assert.hpp"
#include "../cstdlib.hpp"
#include "../type_traits/is_trivial.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			static constexpr mk::stdlib::size_t const s_growth_factor = 2;
		}
	}
}


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>::bits_vector_t() noexcept :
	m_chunks(),
	m_size(),
	m_capacity()
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>::bits_vector_t(mk::stdlib::size_t const& size) noexcept :
	mk::stdlib::bits_vector_t<t, n, chunk_t>()
{
	resize(size);
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>::bits_vector_t(mk::stdlib::bits_vector_t<t, n, chunk_t> const& other) noexcept :
	mk::stdlib::bits_vector_t<t, n, chunk_t>()
{
	mk::stdlib::size_t const chunks_count = element_to_chunk_count(other.m_size);
	m_chunks = static_cast<chunk_t*>(mk::stdlib::malloc(chunks_count * sizeof(chunk_t)));
	m_size = other.m_size;
	m_capacity = chunk_to_element_count(chunks_count);
	mk::stdlib::copy_n(other.m_chunks, chunks_count, m_chunks);
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>::bits_vector_t(mk::stdlib::bits_vector_t<t, n, chunk_t>&& other) noexcept :
	mk::stdlib::bits_vector_t<t, n, chunk_t>()
{
	swap(other);
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>& mk::stdlib::bits_vector_t<t, n, chunk_t>::operator=(mk::stdlib::bits_vector_t<t, n, chunk_t> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	mk::stdlib::size_t const this_chunks_count = chunk_to_element_count(m_size);
	mk::stdlib::size_t const this_chunks_capacity = chunk_to_element_count(m_capacity);
	mk::stdlib::size_t const other_chunks_count = chunk_to_element_count(other.m_size);
	bool const need_reallocate = other_chunks_count > this_chunks_capacity;
	if(need_reallocate)
	{
		mk::stdlib::free(m_chunks);
		m_chunks = mk::stdlib::malloc(other_chunks_count * sizeof(chunk_t));
		mk::stdlib::copy_n(other.m_chunks, other_chunks_count, m_chunks);
		m_size = other.m_size;
		m_capacity = chunk_to_element_count(other_chunks_count);
	}
	else
	{
		mk::stdlib::copy_n(other.m_chunks, other_chunks_count, m_chunks);
		m_size = other.m_size;
	}
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>& mk::stdlib::bits_vector_t<t, n, chunk_t>::operator=(mk::stdlib::bits_vector_t<t, n, chunk_t>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_t<t, n, chunk_t>::~bits_vector_t() noexcept
{
	static_assert(mk::stdlib::is_trivial_t<chunk_t>::s_value);

	mk::stdlib::free(m_chunks);
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::swap(mk::stdlib::bits_vector_t<t, n, chunk_t>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunks, other.m_chunk);
	swap(m_size, other.m_size);
	swap(m_capacity, other.m_capacity);
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_t<t, n, chunk_t>::empty() const noexcept
{
	return m_size == 0;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n, chunk_t>::size() const noexcept
{
	return m_size;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n, chunk_t>::capacity() const noexcept
{
	return m_capacity;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n, chunk_t>::free() const noexcept
{
	return capacity() - size();
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::cbegin() const noexcept
{
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::begin() const noexcept
{
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::cend() const noexcept
{
	mk::stdlib::size_t const idx = m_size;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::end() const noexcept
{
	mk::stdlib::size_t const idx = m_size;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::cfront() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::front() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::cback() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = m_size - 1;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::back() const noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = m_size - 1;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::begin() noexcept
{
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::end() noexcept
{
	mk::stdlib::size_t const idx = m_size;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::front() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = 0;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_t<t, n, chunk_t>::back() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	mk::stdlib::size_t const idx = m_size - 1;
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::reserve(mk::stdlib::size_t const& capacity) noexcept
{
	if(m_capacity >= capacity)
	{
		return;
	}
	mk::stdlib::size_t const geometric_grow = m_capacity * mk::stdlib::impl::s_growth_factor;
	mk::stdlib::size_t const new_capacity = mk::stdlib::max(geometric_grow, capacity);
	mk::stdlib::size_t const new_capacity_chunks = element_to_chunk_count(new_capacity);
	chunk_t* const new_chunks = static_cast<chunk_t*>(mk::stdlib::malloc(new_capacity_chunks * sizeof(chunk_t)));
	mk::stdlib::copy_n(m_chunks, element_to_chunk_count(m_size), new_chunks);
	mk::stdlib::free(m_chunks);
	m_chunks = new_chunks;
	m_capacity = chunk_to_element_count(new_capacity_chunks);
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::resize(mk::stdlib::size_t const& size) noexcept
{
	bool const larger = size > m_size;
	if(larger)
	{
		reserve(size);
		mk::stdlib::size_t const old_chunks_count = element_to_chunk_count(m_size);
		mk::stdlib::size_t const new_chunks_count = element_to_chunk_count(size);
		mk::stdlib::size_t const chunks_diff = new_chunks_count - old_chunks_count;
		mk::stdlib::size_t const last_chunk_diff = s_elements_per_chunk - ((m_size - 1) % s_elements_per_chunk) - 1;
		mk::stdlib::fill_n(begin() + m_size, last_chunk_diff, t{});
		mk::stdlib::fill_n(m_chunks + old_chunks_count, chunks_diff, chunk_t{});
	}
	m_size = size;
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::push_back(t const& val) noexcept
{
	reserve(size() + 1);
	this->operator[](m_size) = val;
	++m_size;
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::pop_back() noexcept
{
	MK_STDLIB_ASSERT(!empty());
	--m_size;
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_t<t, n, chunk_t>::clear() noexcept
{
	m_size = 0;
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n, chunk_t>::element_to_chunk_count(mk::stdlib::size_t const& count) noexcept
{
	mk::stdlib::size_t const ret = (count == 0) ? static_cast<mk::stdlib::size_t>(0) : (((count - 1) / s_elements_per_chunk) + 1);
	return ret;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n, chunk_t>::chunk_to_element_count(mk::stdlib::size_t const& count) noexcept
{
	mk::stdlib::size_t const ret = count * s_elements_per_chunk;
	return ret;
}

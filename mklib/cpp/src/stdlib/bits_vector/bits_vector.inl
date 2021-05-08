#include "bits_vector.hpp"

#include "../algorithm/copy.hpp"
#include "../algorithm/max.hpp"
#include "../assert.hpp"
#include "../cstdlib.hpp"
#include "../memory.hpp"
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


template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>::bits_vector_t() noexcept :
	m_chunks(),
	m_size(),
	m_capacity()
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>::bits_vector_t(mk::stdlib::bits_vector_t<t, n> const& other) noexcept :
	mk::stdlib::bits_vector_t<t, n>()
{
	mk::stdlib::size_t const chunks_size = element_to_chunk_count(other.m_size);
	m_chunks = mk::stdlib::malloc(chunks_size * sizeof(mk::stdlib::bits_vector_chunk_t<t, n>));
	m_size = other.m_size;
	m_capacity = chunk_to_element_count(chunks_size);
	mk::stdlib::uninitialized_copy_n(other.m_chunks, chunks_size, m_chunks);
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>::bits_vector_t(mk::stdlib::bits_vector_t<t, n>&& other) noexcept :
	mk::stdlib::bits_vector_t<t, n>()
{
	swap(other);
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>& mk::stdlib::bits_vector_t<t, n>::operator=(mk::stdlib::bits_vector_t<t, n> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	mk::stdlib::size_t const this_chunks_size = chunk_to_element_count(m_size);
	mk::stdlib::size_t const this_chunks_capacity = chunk_to_element_count(m_capacity);
	mk::stdlib::size_t const other_chunks_size = chunk_to_element_count(other.m_size);
	bool const need_reallocate = other_chunks_size > this_chunks_capacity;
	if(need_reallocate)
	{
		mk::stdlib::destroy_n(m_chunks, this_chunks_size);
		mk::stdlib::free(m_chunks);
		m_chunks = mk::stdlib::malloc(other_chunks_size * sizeof(mk::stdlib::bits_vector_chunk_t<t, n>));
		mk::stdlib::uninitialized_copy_n(other.m_chunks, other_chunks_size, m_chunks);
		m_size = other.m_size;
		m_capacity = chunk_to_element_count(other_chunks_size);
	}
	else
	{
		bool const other_is_bigger = other_chunks_size > this_chunks_size;
		if(other_is_bigger)
		{
			mk::stdlib::size_t const chunks_diff = other_chunks_size - this_chunks_size;
			mk::stdlib::copy_n(other.m_chunks, this_chunks_size, m_chunks);
			mk::stdlib::uninitialized_copy_n(other.m_chunks + this_chunks_size, chunks_diff, m_chunks + this_chunks_size);
			m_size = other.m_size;
		}
		else
		{
			mk::stdlib::size_t const chunks_diff = this_chunks_size - other_chunks_size;
			mk::stdlib::copy_n(other.m_chunks, other_chunks_size, m_chunks);
			mk::stdlib::destroy_n(m_chunks + other_chunks_size, chunks_diff);
			m_size = other.m_size;
		}
	}
	return *this;
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>& mk::stdlib::bits_vector_t<t, n>::operator=(mk::stdlib::bits_vector_t<t, n>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(other);
	return *this;
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_t<t, n>::~bits_vector_t() noexcept
{
	mk::stdlib::destroy_n(m_chunks, element_to_chunk_count(m_size));
	mk::stdlib::free(m_chunks);
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::swap(mk::stdlib::bits_vector_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunks, other.m_chunk);
	swap(m_size, other.m_size);
	swap(m_capacity, other.m_capacity);
}


template<typename t, unsigned n>
[[nodiscard]] bool mk::stdlib::bits_vector_t<t, n>::empty() const noexcept
{
	return m_size != 0;
}

template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n>::size() const noexcept
{
	return m_size;
}

template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n>::capacity() const noexcept
{
	return m_capacity;
}

template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n>::free() const noexcept
{
	return capacity() - size();
}

template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n> mk::stdlib::bits_vector_t<t, n>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n>{m_chunks + chunk_idx, chunk_off};
}


template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n> mk::stdlib::bits_vector_t<t, n>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_reference_t<t, n>{m_chunks + chunk_idx, chunk_off};
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::reserve(mk::stdlib::size_t const& capacity) noexcept
{
	if(m_capacity >= capacity)
	{
		return;
	}
	mk::stdlib::size_t const geometric_grow = m_capacity * mk::stdlib::impl::s_growth_factor;
	mk::stdlib::size_t const new_capacity = mk::stdlib::max(geometric_grow, capacity);
	mk::stdlib::size_t const new_capacity_chunks = element_to_chunk_count(new_capacity);
	mk::stdlib::bits_vector_chunk_t<t, n>* const new_chunks = static_cast<mk::stdlib::bits_vector_chunk_t<t, n>*>(mk::stdlib::malloc(new_capacity_chunks * sizeof(mk::stdlib::bits_vector_chunk_t<t, n>)));
	mk::stdlib::uninitialized_move_destroy_n(m_chunks, element_to_chunk_count(m_size), new_chunks);
	mk::stdlib::free(m_chunks);
	m_chunks = new_chunks;
	m_capacity = chunk_to_element_count(new_capacity_chunks);
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::resize(mk::stdlib::size_t const& size) noexcept
{
	bool const larger = size > m_size;
	if(larger)
	{
		reserve(size);
		mk::stdlib::size_t const old_chunks_count = element_to_chunk_count(m_size);
		mk::stdlib::size_t const new_chunks_count = element_to_chunk_count(size);
		mk::stdlib::size_t const chunks_diff = new_chunks_count - old_chunks_count;
		if(chunks_diff == 0)
		{
			mk::stdlib::size_t const elements_diff = size - m_size;
			for(mk::stdlib::size_t i = 0; i != elements_diff; ++i)
			{
				mk::stdlib::size_t const idx = m_size + i;
				this->operator[](idx) = t{};
			}
		}
		else
		{
			mk::stdlib::uninitialized_default_construct_n(m_chunks + old_chunks_count, chunks_diff);
		}
		m_size = size;
	}
	else
	{
		mk::stdlib::size_t const old_chunks_count = element_to_chunk_count(m_size);
		mk::stdlib::size_t const new_chunks_count = element_to_chunk_count(size);
		mk::stdlib::destroy(m_chunks + new_chunks_count, m_chunks + old_chunks_count);
		m_size = size;
	}
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::push_back(t const& val) noexcept
{
	reserve(size() + 1);
	this->operator[](m_size) = val;
	++m_size;
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::pop_back() noexcept
{
	resize(size() - 1);
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_t<t, n>::clear() noexcept
{
	resize(0);
}


template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n>::element_to_chunk_count(mk::stdlib::size_t const& count) noexcept
{
	mk::stdlib::size_t const ret = (count == 0) ? static_cast<mk::stdlib::size_t>(0) : (((count - 1) / s_elements_per_chunk) + 1);
	return ret;
}

template<typename t, unsigned n>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_vector_t<t, n>::chunk_to_element_count(mk::stdlib::size_t const& count) noexcept
{
	mk::stdlib::size_t const ret = count * s_elements_per_chunk;
	return ret;
}

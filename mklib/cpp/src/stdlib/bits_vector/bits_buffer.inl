#include "bits_buffer.hpp"

#include "../assert.hpp"
#include "../cstdlib.hpp"
#include "../type_traits/is_trivial.hpp"
#include "../utility/swap.hpp"


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_buffer_t<t, n, chunk_t>::bits_buffer_t() noexcept :
	m_chunks()
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_buffer_t<t, n, chunk_t>::bits_buffer_t(mk::stdlib::size_t const& count) noexcept :
	m_chunks(static_cast<chunk_t*>(mk::stdlib::malloc(element_to_chunk_count(count) * sizeof(chunk_t))))
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_buffer_t<t, n, chunk_t>::bits_buffer_t(mk::stdlib::bits_buffer_t<t, n, chunk_t>&& other) noexcept :
	mk::stdlib::bits_buffer_t<t, n, chunk_t>()
{
	swap(other);
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_buffer_t<t, n, chunk_t>& mk::stdlib::bits_buffer_t<t, n, chunk_t>::operator=(mk::stdlib::bits_buffer_t<t, n, chunk_t>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_buffer_t<t, n, chunk_t>::~bits_buffer_t() noexcept
{
	static_assert(mk::stdlib::is_trivial_t<chunk_t>::s_value);

	mk::stdlib::free(m_chunks);
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_buffer_t<t, n, chunk_t>::swap(mk::stdlib::bits_buffer_t<t, n, chunk_t>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunks, other.m_chunk);
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> mk::stdlib::bits_buffer_t<t, n, chunk_t>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_buffer_t<t, n, chunk_t>::operator[](mk::stdlib::size_t const& idx) noexcept
{
	mk::stdlib::size_t const chunk_idx = idx / s_elements_per_chunk;
	mk::stdlib::size_t const chunk_off = idx % s_elements_per_chunk;
	return mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>{m_chunks + chunk_idx, chunk_off};
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t mk::stdlib::bits_buffer_t<t, n, chunk_t>::element_to_chunk_count(mk::stdlib::size_t const& count) noexcept
{
	mk::stdlib::size_t const ret = (count == 0) ? static_cast<mk::stdlib::size_t>(0) : (((count - 1) / s_elements_per_chunk) + 1);
	return ret;
}

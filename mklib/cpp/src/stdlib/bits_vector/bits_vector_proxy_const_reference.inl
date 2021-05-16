#include "bits_vector_proxy_const_reference.hpp"

#include "../assert.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::bits_vector_proxy_const_reference_t() noexcept :
	m_chunk(),
	m_idx()
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::bits_vector_proxy_const_reference_t(chunk_t const* const& chunk, mk::stdlib::size_t const& idx) noexcept :
	m_chunk(chunk),
	m_idx(idx)
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::bits_vector_proxy_const_reference_t(mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> const& other) noexcept :
	m_chunk(other.m_chunk),
	m_idx(other.m_idx)
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::bits_vector_proxy_const_reference_t(mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>&& other) noexcept :
	m_chunk(mk::stdlib::move(other.m_chunk)),
	m_idx(mk::stdlib::move(other.m_idx))
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>& mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::operator=(mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	return *this = static_cast<t>(other);
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::~bits_vector_proxy_const_reference_t() noexcept
{
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::swap(mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunk, other.m_chunk);
	swap(m_idx, other.m_idx);
}


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t>::operator t() const noexcept
{
	return mk::stdlib::bits_vector_chunk_t<t, n, chunk_t>::get(*m_chunk, m_idx);
}

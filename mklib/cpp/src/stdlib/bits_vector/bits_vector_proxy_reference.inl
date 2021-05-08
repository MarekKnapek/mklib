#include "bits_vector_proxy_reference.hpp"

#include "../assert.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"


template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::bits_vector_proxy_reference_t() noexcept :
	m_chunk(),
	m_idx()
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::bits_vector_proxy_reference_t(mk::stdlib::bits_vector_chunk_t<t, n>* const& chunk, mk::stdlib::size_t const& idx) noexcept :
	m_chunk(chunk),
	m_idx(idx)
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::bits_vector_proxy_reference_t(mk::stdlib::bits_vector_proxy_reference_t<t, n> const& other) noexcept :
	m_chunk(other.m_chunk),
	m_idx(other.m_idx)
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::bits_vector_proxy_reference_t(mk::stdlib::bits_vector_proxy_reference_t<t, n>&& other) noexcept :
	m_chunk(mk::stdlib::move(other.m_chunk)),
	m_idx(mk::stdlib::move(other.m_idx))
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>& mk::stdlib::bits_vector_proxy_reference_t<t, n>::operator=(mk::stdlib::bits_vector_proxy_reference_t<t, n> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_chunk = other.m_chunk;
	m_idx = other.m_idx;
	return *this;
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>& mk::stdlib::bits_vector_proxy_reference_t<t, n>::operator=(mk::stdlib::bits_vector_proxy_reference_t<t, n>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_chunk = mk::stdlib::move(other.m_chunk);
	m_idx = mk::stdlib::move(other.m_idx);
	return *this;
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::~bits_vector_proxy_reference_t() noexcept
{
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_proxy_reference_t<t, n>::swap(mk::stdlib::bits_vector_proxy_reference_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunk, other.m_chunk);
	swap(m_idx, other.m_idx);
}


template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>::operator t() const noexcept
{
	t const val = m_chunk->get(m_idx);
	return val;
}


template<typename t, unsigned n>
mk::stdlib::bits_vector_proxy_reference_t<t, n>& mk::stdlib::bits_vector_proxy_reference_t<t, n>::operator=(t const& val) noexcept
{
	m_chunk->set(m_idx, val);
	return *this;
}

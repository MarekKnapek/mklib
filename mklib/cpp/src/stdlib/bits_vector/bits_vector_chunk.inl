#include "bits_vector_chunk.hpp"

#include "../assert.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"


template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>::bits_vector_chunk_t() noexcept :
	m_storage()
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>::bits_vector_chunk_t(mk::stdlib::bits_vector_chunk_t<t, n> const& other) noexcept :
	m_storage(other.m_storage)
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>::bits_vector_chunk_t(mk::stdlib::bits_vector_chunk_t<t, n>&& other) noexcept :
	m_storage(mk::stdlib::move(other.m_storage))
{
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>& mk::stdlib::bits_vector_chunk_t<t, n>::operator=(mk::stdlib::bits_vector_chunk_t<t, n> const& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_storage = other.m_storage;
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>& mk::stdlib::bits_vector_chunk_t<t, n>::operator=(mk::stdlib::bits_vector_chunk_t<t, n>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	m_storage = mk::stdlib::move(other.m_storage);
}

template<typename t, unsigned n>
mk::stdlib::bits_vector_chunk_t<t, n>::~bits_vector_chunk_t() noexcept
{
}

template<typename t, unsigned n>
void mk::stdlib::bits_vector_chunk_t<t, n>::swap(mk::stdlib::bits_vector_chunk_t<t, n>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_storage, other.m_storage);
}


template<typename t, unsigned n>
t mk::stdlib::bits_vector_chunk_t<t, n>::get(mk::stdlib::size_t const& idx) const noexcept
{
	static constexpr storage_t const s_mask = (1u << n) - 1;

	mk::stdlib::size_t const shift_amount = idx * n;
	storage_t const shifted_storage = m_storage >> shift_amount;
	storage_t const masked_storage = shifted_storage & s_mask;
	t const val = static_cast<t>(masked_storage);
	return val;
}


template<typename t, unsigned n>
void mk::stdlib::bits_vector_chunk_t<t, n>::set(mk::stdlib::size_t const& idx, t const& val) noexcept
{
	static constexpr storage_t const s_mask = (1u << n) - 1;

	mk::stdlib::size_t const shift_amount = idx * n;
	storage_t const shifted_mask = s_mask << shift_amount;
	storage_t const cleared_storage = m_storage & ~shifted_mask;
	storage_t const casted_value = static_cast<storage_t>(val);
	storage_t const shifted_value = casted_value << shift_amount;
	storage_t const new_storage = cleared_storage | shifted_value;
	m_storage = new_storage;
}

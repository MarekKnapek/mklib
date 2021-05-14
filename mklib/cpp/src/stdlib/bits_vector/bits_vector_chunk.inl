#include "bits_vector_chunk.hpp"


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] t mk::stdlib::bits_vector_chunk_t<t, n, chunk_t>::get(chunk_t const& chunk, mk::stdlib::size_t const& idx) noexcept
{
	static constexpr chunk_t const s_mask = (static_cast<chunk_t>(1u) << n) - 1;

	mk::stdlib::size_t const shift_amount = idx * n;
	chunk_t const shifted_storage = chunk >> shift_amount;
	chunk_t const masked_storage = shifted_storage & s_mask;
	t const val = static_cast<t>(masked_storage);
	return val;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] chunk_t mk::stdlib::bits_vector_chunk_t<t, n, chunk_t>::set(chunk_t const& chunk, mk::stdlib::size_t const& idx, t const& val) noexcept
{
	static constexpr chunk_t const s_mask = (static_cast<chunk_t>(1u) << n) - 1;

	mk::stdlib::size_t const shift_amount = idx * n;
	chunk_t const shifted_mask = s_mask << shift_amount;
	chunk_t const cleared_storage = chunk & ~shifted_mask;
	chunk_t const casted_value = static_cast<chunk_t>(val);
	chunk_t const shifted_value = casted_value << shift_amount;
	chunk_t const new_storage = cleared_storage | shifted_value;
	return new_storage;
}

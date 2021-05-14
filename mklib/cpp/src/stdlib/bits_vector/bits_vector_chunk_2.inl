#include "bits_vector_chunk_2.hpp"

#include "../assert.hpp"


template<typename t, unsigned n>
template<typename chunk_t>
[[nodiscard]] t mk::stdlib::bits_vector_chunk_2_t<t, n>::get(chunk_t const& chunk, mk::stdlib::size_t const& idx) noexcept
{
	static constexpr chunk_t const s_mask = (1u << n) - 1;

	MK_STDLIB_ASSERT(idx < sizeof(chunk_t) / n);

	mk::stdlib::size_t const shift_amount = idx * n;
	chunk_t const shifted_chunk = chunk >> shift_amount;
	chunk_t const masked_chunk = shifted_chunk & s_mask;
	t const val = static_cast<t>(masked_chunk);
	return val;
}

template<typename t, unsigned n>
template<typename chunk_t>
[[nodiscard]] chunk_t mk::stdlib::bits_vector_chunk_2_t<t, n>::set(chunk_t const& chunk, mk::stdlib::size_t const& idx, t const& val) noexcept
{
	static constexpr chunk_t const s_mask = (1u << n) - 1;

	MK_STDLIB_ASSERT(idx < sizeof(chunk_t) / n);

	mk::stdlib::size_t const shift_amount = idx * n;
	chunk_t const shifted_mask = s_mask << shift_amount;
	chunk_t const cleared_chunk = chunk & ~shifted_mask;
	chunk_t const casted_value = static_cast<chunk_t>(val);
	chunk_t const shifted_value = casted_value << shift_amount;
	chunk_t const new_chunk = cleared_chunk | shifted_value;
	return new_chunk;
}

#include "swap.hpp"

#include "move.hpp"


template<typename t>
constexpr void mk::stdlib::swap(t& a, t&b) noexcept
{
	t tmp = mk::stdlib::move(a);
	a = mk::stdlib::move(b);
	b = mk::stdlib::move(tmp);
}

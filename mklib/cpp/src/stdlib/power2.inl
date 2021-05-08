#include "power2.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			template<unsigned>
			struct power_2_helper_t
			{
				[[nodiscard]] constexpr mk::stdlib::size_t operator()(mk::stdlib::size_t const& n) const noexcept;
			};
			template<>
			struct power_2_helper_t<4>
			{
				[[nodiscard]] constexpr mk::stdlib::uint32_t operator()(mk::stdlib::uint32_t const& n) const noexcept;
			};
			template<>
			struct power_2_helper_t<8>
			{
				[[nodiscard]] constexpr mk::stdlib::uint64_t operator()(mk::stdlib::uint64_t const& n) const noexcept;
			};
		}
	}
}
template<unsigned bytes>
[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::impl::power_2_helper_t<bytes>::operator()(mk::stdlib::size_t const& n) const noexcept
{
	mk::stdlib::size_t x = n;
	--x;
	int shift = 1;
	for(;;)
	{
		x |= x >> shift;
		shift *= 2;
		if(shift == bytes * 8 / 2)
		{
			break;
		}
	}
	++x;
	return x;
}
[[nodiscard]] constexpr mk::stdlib::uint32_t mk::stdlib::impl::power_2_helper_t<4>::operator()(mk::stdlib::uint32_t const& n) const noexcept
{
	mk::stdlib::uint32_t x = n;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	++x;
	return x;
}
[[nodiscard]] constexpr mk::stdlib::uint64_t mk::stdlib::impl::power_2_helper_t<8>::operator()(mk::stdlib::uint64_t const& n) const noexcept
{
	mk::stdlib::uint64_t x = n;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	++x;
	return x;
}


[[nodiscard]] constexpr bool mk::stdlib::is_power_2(mk::stdlib::size_t const& n) noexcept
{
	return n == 0 || (n & (n - 1)) == 0;
}

[[nodiscard]] constexpr mk::stdlib::size_t mk::stdlib::equal_or_greater_power_2(mk::stdlib::size_t const& n) noexcept
{
	if(mk::stdlib::is_power_2(n))
	{
		return n;
	}
	mk::stdlib::size_t const ret = mk::stdlib::impl::power_2_helper_t<sizeof(mk::stdlib::size_t)>{}(n);
	return ret;
}

#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{


		[[nodiscard]] constexpr bool is_power_2(mk::stdlib::size_t const& n) noexcept;
		[[nodiscard]] constexpr mk::stdlib::size_t equal_or_greater_power_2(mk::stdlib::size_t const& n) noexcept;


	}
}


#include "power2.inl"

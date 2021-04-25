#pragma once


#include "../type_traits/remove_reference.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t>
		constexpr void swap(t& a, t&b) noexcept;


	}
}


#include "swap.inl"

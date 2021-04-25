#pragma once


#include "../type_traits/remove_reference.hpp"


namespace mk
{
	namespace stdlib
	{

		template<typename t> [[nodiscard]] constexpr t&& forward(typename mk::stdlib::remove_reference_t<t>::type_t& obj) noexcept;
		template<typename t> [[nodiscard]] constexpr t&& forward(typename mk::stdlib::remove_reference_t<t>::type_t&& obj) noexcept;

	}
}


#include "forward.inl"

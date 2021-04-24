#pragma once


#include "../type_traits/remove_reference.hpp"


namespace mk
{
	namespace stdlib
	{

		template<typename t> [[nodiscard]] constexpr typename mk::stdlib::remove_reference_t<t>::type_t&& move(t&& obj) noexcept;

	}
}


#include "move.inl"

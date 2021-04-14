#pragma once


#include "mk_remove_reference.hpp"


namespace mk
{

	template<typename t> [[nodiscard]] constexpr typename mk::remove_reference_t<t>::type&& move(t&& obj) noexcept;

}


#include "mk_move.inl"

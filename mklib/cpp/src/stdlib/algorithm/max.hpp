#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename... ts>
		[[nodiscard]] constexpr t&& max(t&& a, t&& b, ts&&... rest) noexcept;


	}
}


#include "max.inl"

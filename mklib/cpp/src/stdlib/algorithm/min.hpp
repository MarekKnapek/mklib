#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename... ts>
		[[nodiscard]] constexpr t&& min(t&& a, t&& b, ts&&... rest) noexcept;


	}
}


#include "min.inl"

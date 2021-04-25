#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{

		struct new_t
		{
		};

	}
}


[[nodiscard]] void* operator new(mk::stdlib::size_t const size, void* const& place, mk::stdlib::new_t const& tag) noexcept;

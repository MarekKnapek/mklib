#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{
		
		void cstdlib_init() noexcept;
		void cstdlib_deinit() noexcept;

		[[nodiscard]] void* malloc(mk::stdlib::size_t const& count) noexcept;
		void free(void* const& ptr) noexcept;
	
	
	}
}

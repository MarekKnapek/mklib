#pragma once


#include "../stdlib/size.hpp" // mk::stdlib::size_t


namespace mk
{
	namespace runtime
	{


		void asan_poison_memory_region(void const* const& addr, mk::stdlib::size_t const& size) noexcept;
		void asan_unpoison_memory_region(void const* const& addr, mk::stdlib::size_t const& size) noexcept;


	}
}

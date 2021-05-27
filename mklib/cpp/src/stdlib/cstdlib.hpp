#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{


		class cstdlib_init_t
		{
		public:
			cstdlib_init_t() noexcept;
			cstdlib_init_t(mk::stdlib::cstdlib_init_t const&) noexcept = delete;
			cstdlib_init_t(mk::stdlib::cstdlib_init_t&&) noexcept = delete;
			mk::stdlib::cstdlib_init_t& operator=(mk::stdlib::cstdlib_init_t const&) noexcept = delete;
			mk::stdlib::cstdlib_init_t& operator=(mk::stdlib::cstdlib_init_t&&) noexcept = delete;
			~cstdlib_init_t() noexcept;
		};

		void cstdlib_init() noexcept;
		void cstdlib_deinit() noexcept;


		[[nodiscard]] void* malloc(mk::stdlib::size_t const& count) noexcept;
		void free(void const* const& ptr) noexcept;
	
	
	}
}

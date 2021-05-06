#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename... ts> constexpr t* construct_at(t* const& ptr, ts&&... params) noexcept;
		template<typename t> constexpr void destroy(t& val) noexcept;
		template<typename t> constexpr void destroy_at(t const& it) noexcept;

		template<typename t, typename u> void uninitialized_default_construct(t const& begin, u const& end) noexcept;
		template<typename t, typename u, typename v> v uninitialized_copy(t const& input_begin, u const& input_end, v const& output_begin) noexcept;
		template<typename t, typename u, typename v> v uninitialized_move(t const& input_begin, u const& input_end, v const& output_begin) noexcept;
		template<typename t, typename u, typename v> v uninitialized_move_destroy(t const& input_begin, u const& input_end, v const& output_begin) noexcept;
		template<typename t, typename u> constexpr void destroy(t const& begin, u const& end) noexcept;

		template<typename t, typename u, typename v> v uninitialized_copy_n(t const& input_begin, u const& size, v const& output_begin) noexcept;
		template<typename t, typename u, typename v> v uninitialized_move_destroy_n(t const& input_begin, u const& input_size, v const& output_begin) noexcept;
		template<typename t, typename u> constexpr t destroy_n(t const& begin, u const& size) noexcept;


	}
}


#include "memory.inl"

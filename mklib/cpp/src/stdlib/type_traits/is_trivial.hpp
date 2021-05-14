#pragma once


#include "../ints.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename> struct is_trivial_t { static constexpr bool const s_value = false; };

		template<typename t> struct is_trivial_t<t*> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::uint8_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::uint16_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::uint32_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::uint64_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::int8_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::int16_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::int32_t> { static constexpr bool const s_value = true; };
		template<> struct is_trivial_t<mk::stdlib::int64_t> { static constexpr bool const s_value = true; };


	}
}

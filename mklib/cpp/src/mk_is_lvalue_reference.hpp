#pragma once


namespace mk
{

	template<typename> struct is_lvalue_reference_t { static constexpr bool const s_value = false; };
	template<typename t> struct is_lvalue_reference_t<t&> { static constexpr bool const s_value = true; };

}

#pragma once


namespace mk
{

	template<typename, typename> struct is_same_t { static constexpr bool const s_value = false; };
	template<typename t> struct is_same_t<t, t> { static constexpr bool const s_value = true; };

}

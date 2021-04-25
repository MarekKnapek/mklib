#include "forward.hpp"


template<typename t>
[[nodiscard]] constexpr t&& mk::stdlib::forward(typename mk::stdlib::remove_reference_t<t>::type_t& obj) noexcept
{
	return static_cast<t&&>(obj);
}

template<typename t>
[[nodiscard]] constexpr t&& mk::stdlib::forward(typename mk::stdlib::remove_reference_t<t>::type_t&& obj) noexcept
{
	//static_assert(!mk::stdlib::is_lvalue_reference_t<t>::s_value);
	return static_cast<t&&>(obj);
}

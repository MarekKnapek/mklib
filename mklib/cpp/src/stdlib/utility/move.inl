#include "move.hpp"


template<typename t>
[[nodiscard]] constexpr typename mk::stdlib::remove_reference_t<t>::type_t&& mk::stdlib::move(t&& obj) noexcept
{
	return static_cast<typename mk::stdlib::remove_reference_t<t>::type_t&&>(obj);
}

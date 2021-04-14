#include "mk_move.hpp"


template<typename t>
[[nodiscard]] constexpr typename mk::remove_reference_t<t>::type&& mk::move(t&& obj) noexcept
{
	return static_cast<typename mk::remove_reference_t<t>::type&&>(obj);
}

#include "max.hpp"

#include "../type_traits/is_same.hpp"
#include "../utility/forward.hpp"

#define _ALLOW_RTCc_IN_STL
//#include <utility>


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			template<typename t>
			[[nodiscard]] constexpr t&& max(t&& obj) noexcept;
			template<typename t, typename... ts>
			[[nodiscard]] constexpr t&& max(t&& a, t&& b, ts&&... rest) noexcept;
		}
	}
}


template<typename t, typename... ts>
[[nodiscard]] constexpr t&& mk::stdlib::max(t&& a, t&& b, ts&&... rest) noexcept
{
	static_assert((mk::stdlib::is_same_t<t, ts>::s_value && ...));
	return mk::stdlib::impl::max(mk::stdlib::forward<t>(a), mk::stdlib::forward<t>(b), mk::stdlib::forward<ts>(rest)...);
}


template<typename t>
[[nodiscard]] constexpr t&& mk::stdlib::impl::max(t&& obj) noexcept
{
	return mk::stdlib::forward<t>(obj);
}

template<typename t, typename... ts>
[[nodiscard]] constexpr t&& mk::stdlib::impl::max(t&& a, t&& b, ts&&... rest) noexcept
{
	return
		b < a ?
		mk::stdlib::impl::max(mk::stdlib::forward<t>(a), mk::stdlib::forward<ts>(rest)...) :
		mk::stdlib::impl::max(mk::stdlib::forward<t>(b), mk::stdlib::forward<ts>(rest)...);
}

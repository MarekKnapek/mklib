#include "min.hpp"

#include "../type_traits/is_same.hpp"
#include "../utility/forward.hpp"


namespace mk
{
	namespace stdlib
	{
		namespace impl
		{
			template<typename t>
			[[nodiscard]] constexpr t&& min(t&& obj) noexcept;
			template<typename t, typename... ts>
			[[nodiscard]] constexpr t&& min(t&& a, t&& b, ts&&... rest) noexcept;
		}
	}
}


template<typename t, typename... ts>
[[nodiscard]] constexpr t&& mk::stdlib::min(t&& a, t&& b, ts&&... rest) noexcept
{
	static_assert((mk::stdlib::is_same_t<t, ts>::s_value && ...));
	return mk::stdlib::impl::min(mk::stdlib::forward<t>(a), mk::stdlib::forward<t>(b), mk::stdlib::forward<ts>(rest)...);
}


template<typename t>
[[nodiscard]] constexpr t&& mk::stdlib::impl::min(t&& obj) noexcept
{
	return mk::stdlib::forward<t>(obj);
}

template<typename t, typename... ts>
[[nodiscard]] constexpr t&& mk::stdlib::impl::min(t&& a, t&& b, ts&&... rest) noexcept
{
	return
		b < a ?
		mk::stdlib::impl::min(mk::stdlib::forward<t>(b), mk::stdlib::forward<ts>(rest)...) :
		mk::stdlib::impl::min(mk::stdlib::forward<t>(a), mk::stdlib::forward<ts>(rest)...);
}

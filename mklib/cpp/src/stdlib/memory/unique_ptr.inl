#include "unique_ptr.hpp"


template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator==(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return a.get() == b.get();
}

template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator!=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return !(a == b);
}

template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator<(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return a.get() < b.get();
}

template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator>(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return b < a;
}

template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator<=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return !(a > b);
}

template<typename t, typename d>
[[nodiscard]] bool mk::stdlib::operator>=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept
{
	return !(a < b);
}

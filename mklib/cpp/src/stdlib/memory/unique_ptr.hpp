#pragma once


#include "unique_ptr_single.hpp"
#include "unique_ptr_multi.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename d> [[nodiscard]] bool operator==(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;
		template<typename t, typename d> [[nodiscard]] bool operator!=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;
		template<typename t, typename d> [[nodiscard]] bool operator<(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;
		template<typename t, typename d> [[nodiscard]] bool operator>(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;
		template<typename t, typename d> [[nodiscard]] bool operator<=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;
		template<typename t, typename d> [[nodiscard]] bool operator>=(mk::stdlib::unique_ptr_t<t, d> const& a, mk::stdlib::unique_ptr_t<t, d> const& b) noexcept;


	}
}


#include "unique_ptr.inl"

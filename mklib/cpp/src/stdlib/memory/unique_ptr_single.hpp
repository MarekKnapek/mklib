#pragma once


#include "../type_traits/enable_if.hpp" // mk::stdlib::mk::stdlib::enable_if_t
#include "../type_traits/is_array.hpp" // mk::stdlib::is_array_t
#include "default_deleter.h" // mk::stdlib::default_deleter_t


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename d = mk::stdlib::default_deleter_t<t>>
		class unique_ptr_t
		{
		public:
			unique_ptr_t() noexcept;
			explicit unique_ptr_t(t* const& ptr) noexcept;
			unique_ptr_t(mk::stdlib::unique_ptr_t<t, d> const&) noexcept = delete;
			unique_ptr_t(mk::stdlib::unique_ptr_t<t, d>&& other) noexcept;
			mk::stdlib::unique_ptr_t<t, d>& operator=(mk::stdlib::unique_ptr_t<t, d> const&) noexcept = delete;
			mk::stdlib::unique_ptr_t<t, d>& operator=(mk::stdlib::unique_ptr_t<t, d>&& other) noexcept;
			~unique_ptr_t() noexcept;
			void swap(mk::stdlib::unique_ptr_t<t, d>& other) noexcept;
		public:
			[[nodiscard]] t* const& get() const noexcept;
			[[nodiscard]] explicit operator bool() const noexcept;
			[[nodiscard]] t* operator->() const noexcept;
			[[nodiscard]] t& operator*() const noexcept;
		public:
			[[nodiscard]] t* release() noexcept;
			void reset(t* const& ptr) noexcept;
		private:
			t* m_ptr;
		};

		template<typename t, typename d> inline void swap(mk::stdlib::unique_ptr_t<t, d>& a, mk::stdlib::unique_ptr_t<t, d>& b) noexcept { a.swap(b); }

		template<typename t, typename... ts, typename mk::stdlib::enable_if_t<!mk::stdlib::is_array_t<t>::s_value ,void*>::type_t = nullptr> mk::stdlib::unique_ptr_t<t> make_unique(ts&&... vals) noexcept;


	}
}


#include "unique_ptr_single.inl"

#pragma once


#include "../size.hpp" // mk::stdlib::size_t
#include "default_deleter.h" // mk::stdlib::default_deleter_t


namespace mk { namespace stdlib { template<typename t, typename = mk::stdlib::default_deleter_t<t>> class unique_ptr_t; } }


namespace mk
{
	namespace stdlib
	{


		template<typename t, typename d>
		class unique_ptr_t<t[], d>
		{
		public:
			unique_ptr_t() noexcept;
			explicit unique_ptr_t(t* const& ptr) noexcept;
			unique_ptr_t(mk::stdlib::unique_ptr_t<t[], d> const&) noexcept = delete;
			unique_ptr_t(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept;
			mk::stdlib::unique_ptr_t<t[], d>& operator=(mk::stdlib::unique_ptr_t<t[], d> const&) noexcept = delete;
			mk::stdlib::unique_ptr_t<t[], d>& operator=(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept;
			~unique_ptr_t() noexcept;
			void swap(mk::stdlib::unique_ptr_t<t[], d>& other) noexcept;
		public:
			[[nodiscard]] t* const& get() const noexcept;
			[[nodiscard]] explicit operator bool() const noexcept;
			[[nodiscard]] t& operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] t* release() noexcept;
			void reset(t* const& ptr) noexcept;
		private:
			t* m_ptr;
		};

		template<typename t, typename d> inline void swap(mk::stdlib::unique_ptr_t<t[], d>& a, mk::stdlib::unique_ptr_t<t[], d>& b) noexcept { a.swap(b); }

		template<typename t> mk::stdlib::unique_ptr_t<t> make_unique(mk::stdlib::size_t const& count) noexcept;


	}
}


#include "unique_ptr_multi.inl"

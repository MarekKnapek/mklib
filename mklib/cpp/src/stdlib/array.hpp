#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, mk::stdlib::size_t n>
		class array_t
		{
		public:
			constexpr void swap(mk::stdlib::array_t<t, n>& other) noexcept;
			[[nodiscard]] constexpr mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] constexpr t const* cbegin() const noexcept;
			[[nodiscard]] constexpr t const* begin() const noexcept;
			[[nodiscard]] constexpr t const* cend() const noexcept;
			[[nodiscard]] constexpr t const* end() const noexcept;
			[[nodiscard]] constexpr t const* cdata() const noexcept;
			[[nodiscard]] constexpr t const* data() const noexcept;
			[[nodiscard]] constexpr t const& cfront() const noexcept;
			[[nodiscard]] constexpr t const& front() const noexcept;
			[[nodiscard]] constexpr t const& cback() const noexcept;
			[[nodiscard]] constexpr t const& back() const noexcept;
			[[nodiscard]] constexpr t const& operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] constexpr t* begin() noexcept;
			[[nodiscard]] constexpr t* end() noexcept;
			[[nodiscard]] constexpr t* data() noexcept;
			[[nodiscard]] constexpr t& front() noexcept;
			[[nodiscard]] constexpr t& back() noexcept;
			[[nodiscard]] constexpr t& operator[](mk::stdlib::size_t const& idx) noexcept;
		public:
			t m_array[n];
		};


	}
}


#include "array.inl"

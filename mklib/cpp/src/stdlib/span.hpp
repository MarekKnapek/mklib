#pragma once


#include "size.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t>
		class span_t
		{
		public:
			constexpr span_t() noexcept;
			constexpr span_t(t* const& data, mk::stdlib::size_t const& size) noexcept;
			constexpr span_t(t* const& begin, t const* const& end) noexcept;
			template<mk::stdlib::size_t n> constexpr span_t(t(&arr)[n]) noexcept;
			constexpr span_t(mk::stdlib::span_t<t> const& other) noexcept;
			constexpr span_t(mk::stdlib::span_t<t>&& other) noexcept;
			constexpr mk::stdlib::span_t<t>& operator=(mk::stdlib::span_t<t> const& other) noexcept;
			constexpr mk::stdlib::span_t<t>& operator=(mk::stdlib::span_t<t>&& other) noexcept;
			constexpr ~span_t() noexcept;
			constexpr void swap(mk::stdlib::span_t<t>& other) noexcept;
		public:
			[[nodiscard]] constexpr t const* cdata() const noexcept;
			[[nodiscard]] constexpr t const* data() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] constexpr bool empty() const noexcept;
			[[nodiscard]] constexpr t const* cbegin() const noexcept;
			[[nodiscard]] constexpr t const* begin() const noexcept;
			[[nodiscard]] constexpr t const* cend() const noexcept;
			[[nodiscard]] constexpr t const* end() const noexcept;
			[[nodiscard]] constexpr t const& cfront() const noexcept;
			[[nodiscard]] constexpr t const& front() const noexcept;
			[[nodiscard]] constexpr t const& cback() const noexcept;
			[[nodiscard]] constexpr t const& back() const noexcept;
			[[nodiscard]] constexpr t const& operator[](mk::stdlib::size_t const& idx) const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t> first(mk::stdlib::size_t const& count) const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t> last(mk::stdlib::size_t const& count) const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t> sub_span(mk::stdlib::size_t const& offset, mk::stdlib::size_t const& count) const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t const> as_const() const noexcept;
		public:
			[[nodiscard]] constexpr t* data() noexcept;
			[[nodiscard]] constexpr t* begin() noexcept;
			[[nodiscard]] constexpr t* end() noexcept;
			[[nodiscard]] constexpr t& front() noexcept;
			[[nodiscard]] constexpr t& back() noexcept;
			[[nodiscard]] constexpr t& operator[](mk::stdlib::size_t const& idx) noexcept;
		private:
			t* m_data;
			mk::stdlib::size_t m_size;
		};

		template<typename t> constexpr inline void swap(mk::stdlib::span_t<t>& a, mk::stdlib::span_t<t>& b) noexcept { a.swap(b); }


	}
}


#include "span.inl"

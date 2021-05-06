#pragma once


#include "array.hpp"
#include "size.hpp"
#include "power2.hpp"
#include "type_traits/aligned_storage.hpp"
#include "span.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, mk::stdlib::size_t n>
		class ring_buffer_t
		{
		public:
			ring_buffer_t() noexcept;
			ring_buffer_t(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept;
			ring_buffer_t(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept;
			mk::stdlib::ring_buffer_t<t, n>& operator=(mk::stdlib::ring_buffer_t<t, n> const& other) noexcept;
			mk::stdlib::ring_buffer_t<t, n>& operator=(mk::stdlib::ring_buffer_t<t, n>&& other) noexcept;
			~ring_buffer_t() noexcept;
			void swap(mk::stdlib::ring_buffer_t<t, n>& other) noexcept;
		public:
			[[nodiscard]] constexpr bool empty() const noexcept;
			[[nodiscard]] constexpr bool full() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::size_t capacity() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::size_t free() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t const> first_half() const noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t const> second_half() const noexcept;
			[[nodiscard]] constexpr t const& operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] constexpr mk::stdlib::span_t<t> first_half() noexcept;
			[[nodiscard]] constexpr mk::stdlib::span_t<t> second_half() noexcept;
			[[nodiscard]] constexpr t& operator[](mk::stdlib::size_t const& idx) noexcept;
			template<typename u> constexpr t& push_back(u&& obj) noexcept;
			void pop_front() noexcept;
		public:
			static constexpr mk::stdlib::size_t const s_capacity = mk::stdlib::equal_or_greater_power_2(n);
			static constexpr mk::stdlib::size_t const s_mask = s_capacity - 1;
		private:
			mk::stdlib::array_t<mk::stdlib::aligned_storage_helper_t<t>, s_capacity> m_array;
			mk::stdlib::size_t m_read;
			mk::stdlib::size_t m_write;
		};


	}
}


#include "ring_buffer.inl"

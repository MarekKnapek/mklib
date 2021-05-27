#pragma once


#include "array.hpp" // mk::stdlib::array_t
#include "power2.hpp" // mk::stdlib::equal_or_greater_power_2
#include "size.hpp" // mk::stdlib::size_t
#include "span.hpp" // mk::stdlib::span_t
#include "type_traits/aligned_storage.hpp" // mk::stdlib::aligned_storage_helper_t


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
			[[nodiscard]] bool empty() const noexcept;
			[[nodiscard]] bool full() const noexcept;
			[[nodiscard]] mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] mk::stdlib::size_t capacity() const noexcept;
			[[nodiscard]] mk::stdlib::size_t free() const noexcept;
			[[nodiscard]] mk::stdlib::span_t<t const> first_half() const noexcept;
			[[nodiscard]] mk::stdlib::span_t<t const> second_half() const noexcept;
			[[nodiscard]] t const& operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] mk::stdlib::span_t<t> first_half() noexcept;
			[[nodiscard]] mk::stdlib::span_t<t> second_half() noexcept;
			[[nodiscard]] t& operator[](mk::stdlib::size_t const& idx) noexcept;
			template<typename u> t& push_back(u&& obj) noexcept;
			void pop_back() noexcept;
			void pop_back(mk::stdlib::size_t const& count) noexcept;
			void pop_front() noexcept;
			void pop_front(mk::stdlib::size_t const& count) noexcept;
			void clear() noexcept;
		public:
			static constexpr mk::stdlib::size_t const s_capacity = mk::stdlib::equal_or_greater_power_2(n);
			static constexpr mk::stdlib::size_t const s_mask = s_capacity - 1;
		private:
			mk::stdlib::array_t<mk::stdlib::aligned_storage_helper_t<t>, s_capacity> m_array;
			mk::stdlib::size_t m_read;
			mk::stdlib::size_t m_write;
		};

		template<typename t, mk::stdlib::size_t n> inline void swap(mk::stdlib::ring_buffer_t<t, n>& a, mk::stdlib::ring_buffer_t<t, n>& b) noexcept { a.swap(b); }


	}
}


#include "ring_buffer.inl"

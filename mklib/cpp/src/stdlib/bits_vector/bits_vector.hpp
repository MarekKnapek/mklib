#pragma once


#include "../climits.hpp"
#include "../size.hpp"
#include "bits_vector_chunk.hpp"
#include "bits_vector_proxy_const_reference.hpp"
#include "bits_vector_proxy_reference.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n>
		class bits_vector_t
		{
		public:
			bits_vector_t() noexcept;
			bits_vector_t(mk::stdlib::bits_vector_t<t, n> const& other) noexcept;
			bits_vector_t(mk::stdlib::bits_vector_t<t, n>&& other) noexcept;
			mk::stdlib::bits_vector_t<t, n>& operator=(mk::stdlib::bits_vector_t<t, n> const& other) noexcept;
			mk::stdlib::bits_vector_t<t, n>& operator=(mk::stdlib::bits_vector_t<t, n>&& other) noexcept;
			~bits_vector_t() noexcept;
			void swap(mk::stdlib::bits_vector_t<t, n>& other) noexcept;
		public:
			[[nodiscard]] bool empty() const noexcept;
			[[nodiscard]] mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] mk::stdlib::size_t capacity() const noexcept;
			[[nodiscard]] mk::stdlib::size_t free() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n> operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n> operator[](mk::stdlib::size_t const& idx) noexcept;
			void reserve(mk::stdlib::size_t const& capacity) noexcept;
			void resize(mk::stdlib::size_t const& size) noexcept;
			void push_back(t const& val) noexcept;
			void pop_back() noexcept;
			void clear() noexcept;
		private:
			static constexpr mk::stdlib::size_t const s_elements_per_chunk = sizeof(mk::stdlib::bits_vector_chunk_t<t, n>) * mk::stdlib::s_char_bit / n;
			[[nodiscard]] static mk::stdlib::size_t element_to_chunk_count(mk::stdlib::size_t const& count) noexcept;
			[[nodiscard]] static mk::stdlib::size_t chunk_to_element_count(mk::stdlib::size_t const& count) noexcept;
		private:
			mk::stdlib::bits_vector_chunk_t<t, n>* m_chunks;
			mk::stdlib::size_t m_size;
			mk::stdlib::size_t m_capacity;
		};

		template<typename t, unsigned n> inline void swap(mk::stdlib::bits_vector_t<t, n>& a, mk::stdlib::bits_vector_t<t, n>& b) noexcept { a.swap(b); }


	}
}


#include "bits_vector.inl"

#pragma once


#include "../climits.hpp"
#include "../size.hpp"
#include "bits_vector_chunk.hpp"
#include "bits_vector_proxy_const_reference.hpp"
#include "bits_vector_proxy_reference.hpp"
#include "bits_vector_const_iterator.hpp"
#include "bits_vector_iterator.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n, typename chunk_t = mk::stdlib::size_t>
		class bits_vector_t
		{
		public:
			bits_vector_t() noexcept;
			bits_vector_t(mk::stdlib::size_t const& size) noexcept;
			bits_vector_t(mk::stdlib::bits_vector_t<t, n, chunk_t> const& other) noexcept;
			bits_vector_t(mk::stdlib::bits_vector_t<t, n, chunk_t>&& other) noexcept;
			mk::stdlib::bits_vector_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_t<t, n, chunk_t> const& other) noexcept;
			mk::stdlib::bits_vector_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_t<t, n, chunk_t>&& other) noexcept;
			~bits_vector_t() noexcept;
			void swap(mk::stdlib::bits_vector_t<t, n, chunk_t>& other) noexcept;
		public:
			[[nodiscard]] bool empty() const noexcept;
			[[nodiscard]] mk::stdlib::size_t size() const noexcept;
			[[nodiscard]] mk::stdlib::size_t capacity() const noexcept;
			[[nodiscard]] mk::stdlib::size_t free() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> operator[](mk::stdlib::size_t const& idx) const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> cbegin() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> begin() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> cend() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> end() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> cfront() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> front() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> cback() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> back() const noexcept;
		public:
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> operator[](mk::stdlib::size_t const& idx) noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> begin() noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> end() noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> front() noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> back() noexcept;
			void reserve(mk::stdlib::size_t const& capacity) noexcept;
			void resize(mk::stdlib::size_t const& size) noexcept;
			void push_back(t const& val) noexcept;
			void pop_back() noexcept;
			void clear() noexcept;
		private:
			static constexpr mk::stdlib::size_t const s_elements_per_chunk = sizeof(chunk_t) * mk::stdlib::s_char_bit / n;
			[[nodiscard]] static mk::stdlib::size_t element_to_chunk_count(mk::stdlib::size_t const& count) noexcept;
			[[nodiscard]] static mk::stdlib::size_t chunk_to_element_count(mk::stdlib::size_t const& count) noexcept;
		private:
			chunk_t* m_chunks;
			mk::stdlib::size_t m_size;
			mk::stdlib::size_t m_capacity;
		};

		template<typename t, unsigned n, typename chunk_t> inline void swap(mk::stdlib::bits_vector_t<t, n, chunk_t>& a, mk::stdlib::bits_vector_t<t, n, chunk_t>& b) noexcept { a.swap(b); }


	}
}


#include "bits_vector.inl"

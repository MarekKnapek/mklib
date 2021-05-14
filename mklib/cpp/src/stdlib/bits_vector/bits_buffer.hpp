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


		template<typename t, unsigned n, typename chunk_t = mk::stdlib::size_t>
		class bits_buffer_t
		{
		public:
			bits_buffer_t() noexcept;
			bits_buffer_t(mk::stdlib::size_t const& count) noexcept;
			bits_buffer_t(mk::stdlib::bits_buffer_t<t, n, chunk_t> const&) noexcept = delete;
			bits_buffer_t(mk::stdlib::bits_buffer_t<t, n, chunk_t>&& other) noexcept;
			mk::stdlib::bits_buffer_t<t, n, chunk_t>& operator=(mk::stdlib::bits_buffer_t<t, n, chunk_t> const&) noexcept = delete;
			mk::stdlib::bits_buffer_t<t, n, chunk_t>& operator=(mk::stdlib::bits_buffer_t<t, n, chunk_t>&& other) noexcept;
			~bits_buffer_t() noexcept;
			void swap(mk::stdlib::bits_buffer_t<t, n, chunk_t>& other) noexcept;
		public:
			[[nodiscard]] mk::stdlib::bits_vector_proxy_const_reference_t<t, n, chunk_t> operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> operator[](mk::stdlib::size_t const& idx) noexcept;
		private:
			static constexpr mk::stdlib::size_t const s_elements_per_chunk = sizeof(chunk_t) * mk::stdlib::s_char_bit / n;
			[[nodiscard]] static mk::stdlib::size_t element_to_chunk_count(mk::stdlib::size_t const& count) noexcept;
		private:
			chunk_t* m_chunks;
		};

		template<typename t, unsigned n, typename chunk_t> inline void swap(mk::stdlib::bits_buffer_t<t, n, chunk_t>& a, mk::stdlib::bits_buffer_t<t, n, chunk_t>& b) noexcept { a.swap(b); }


	}
}


#include "bits_buffer.inl"

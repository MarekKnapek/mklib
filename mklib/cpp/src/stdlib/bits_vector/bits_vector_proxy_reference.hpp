#pragma once


#include "../size.hpp"
#include "bits_vector_chunk.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n, typename chunk_t = mk::stdlib::size_t>
		class bits_vector_proxy_reference_t
		{
		public:
			bits_vector_proxy_reference_t() noexcept;
			bits_vector_proxy_reference_t(chunk_t* const& chunk, mk::stdlib::size_t const& idx) noexcept;
			bits_vector_proxy_reference_t(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> const& other) noexcept;
			bits_vector_proxy_reference_t(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>&& other) noexcept;
			mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> const& other) noexcept;
			mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>&& other) noexcept;
			~bits_vector_proxy_reference_t() noexcept;
			void swap(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& other) noexcept;
		public:
			operator t() const noexcept;
		public:
			mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& operator=(t const& val) noexcept;
		private:
			chunk_t* m_chunk;
			mk::stdlib::size_t m_idx;
		};

		template<typename t, unsigned n, typename chunk_t> inline void swap(mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& a, mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>& b) noexcept { a.swap(b); }


	}
}


#include "bits_vector_proxy_reference.inl"

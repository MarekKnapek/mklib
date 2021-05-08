#pragma once


#include "../size.hpp"
#include "bits_vector_chunk.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n>
		class bits_vector_proxy_const_reference_t
		{
		public:
			bits_vector_proxy_const_reference_t() noexcept;
			bits_vector_proxy_const_reference_t(mk::stdlib::bits_vector_chunk_t<t, n> const* const& chunk, mk::stdlib::size_t const& idx) noexcept;
			bits_vector_proxy_const_reference_t(mk::stdlib::bits_vector_proxy_const_reference_t<t, n> const& other) noexcept;
			bits_vector_proxy_const_reference_t(mk::stdlib::bits_vector_proxy_const_reference_t<t, n>&& other) noexcept;
			mk::stdlib::bits_vector_proxy_const_reference_t<t, n>& operator=(mk::stdlib::bits_vector_proxy_const_reference_t<t, n> const& other) noexcept;
			mk::stdlib::bits_vector_proxy_const_reference_t<t, n>& operator=(mk::stdlib::bits_vector_proxy_const_reference_t<t, n>&& other) noexcept;
			~bits_vector_proxy_const_reference_t() noexcept;
			void swap(mk::stdlib::bits_vector_proxy_const_reference_t<t, n>& other) noexcept;
		public:
			operator t() const noexcept;
		public:
			t& operator=(t const& val) noexcept = delete;
		private:
			mk::stdlib::bits_vector_chunk_t<t, n> const* m_chunk;
			mk::stdlib::size_t m_idx;
		};

		template<typename t, unsigned n> inline void swap(mk::stdlib::bits_vector_proxy_const_reference_t<t, n>& a, mk::stdlib::bits_vector_proxy_const_reference_t<t, n>& b) noexcept { a.swap(b); }


	}
}


#include "bits_vector_proxy_const_reference.inl"

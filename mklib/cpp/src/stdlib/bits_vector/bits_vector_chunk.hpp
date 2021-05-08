#pragma once


#include "../size.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n>
		class bits_vector_chunk_t
		{
		public:
			bits_vector_chunk_t() noexcept;
			bits_vector_chunk_t(mk::stdlib::bits_vector_chunk_t<t, n> const& other) noexcept;
			bits_vector_chunk_t(mk::stdlib::bits_vector_chunk_t<t, n>&& other) noexcept;
			mk::stdlib::bits_vector_chunk_t<t, n>& operator=(mk::stdlib::bits_vector_chunk_t<t, n> const& other) noexcept;
			mk::stdlib::bits_vector_chunk_t<t, n>& operator=(mk::stdlib::bits_vector_chunk_t<t, n>&& other) noexcept;
			~bits_vector_chunk_t<t, n>() noexcept;
			void swap(mk::stdlib::bits_vector_chunk_t<t, n>& other) noexcept;
		public:
			t get(mk::stdlib::size_t const& idx) const noexcept;
		public:
			void set(mk::stdlib::size_t const& idx, t const& val) noexcept;
		private:
			typedef mk::stdlib::size_t storage_t;
			storage_t m_storage;
		};

		template<typename t, unsigned n> void swap(mk::stdlib::bits_vector_chunk_t<t, n>& a, mk::stdlib::bits_vector_chunk_t<t, n>& b) noexcept { a.swap(b); }


	}
}


#include "bits_vector_chunk.inl"

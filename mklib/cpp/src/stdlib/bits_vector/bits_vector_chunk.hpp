#pragma once


#include "../size.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n, typename chunk_t>
		class bits_vector_chunk_t
		{
		public:
			[[nodiscard]] static t get(chunk_t const& chunk, mk::stdlib::size_t const& idx) noexcept;
			[[nodiscard]] static chunk_t set(chunk_t const& chunk, mk::stdlib::size_t const& idx, t const& val) noexcept;
		};


	}
}


#include "bits_vector_chunk.inl"

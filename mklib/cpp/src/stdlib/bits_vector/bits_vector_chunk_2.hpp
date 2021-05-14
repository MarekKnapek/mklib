#pragma once


#include "../size.hpp"


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n>
		struct bits_vector_chunk_2_t
		{
			template<typename chunk_t> [[nodiscard]] static t get(chunk_t const& chunk, mk::stdlib::size_t const& idx) noexcept;
			template<typename chunk_t> [[nodiscard]] static chunk_t set(chunk_t const& chunk, mk::stdlib::size_t const& idx, t const& val) noexcept;
		};


	}
}


#include "bits_vector_chunk_2.inl"

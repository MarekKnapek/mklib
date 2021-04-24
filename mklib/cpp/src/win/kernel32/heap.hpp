#pragma once


#include "../../stdlib/ints.hpp"
#include "../../stdlib/size.hpp"
#include "../types.hpp"


namespace mk
{
	namespace win
	{
		namespace kernel32
		{


			enum class heap_create_t : mk::stdlib::uint32_t
			{
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				enable_execute      = 0x00040000,
			};

			enum class heap_alloc_t : mk::stdlib::uint32_t
			{
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				zero_memory         = 0x00000008,
			};

			enum class heap_size_t
			{
				no_serialize = 0x00000001,
			};

			enum class heap_realloc_t : mk::stdlib::uint32_t
			{
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				zero_memory         = 0x00000008,
				in_place_only       = 0x00000010,
			};

			enum class heap_free_t : mk::stdlib::uint32_t
			{
				no_serialize = 0x00000001,
			};


			mk::win::handle_t get_process_heap(void) noexcept;
			mk::win::handle_t heap_create(mk::win::kernel32::heap_create_t const& options, mk::stdlib::size_t const& initial_size, mk::stdlib::size_t const& maximum_size) noexcept;
			void* heap_alloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_alloc_t const& flags, mk::stdlib::size_t const& bytes) noexcept;
			mk::stdlib::size_t heap_size(mk::win::handle_t const& heap, mk::win::kernel32::heap_size_t const& flags, void const* const& mem) noexcept;
			void* heap_realloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_realloc_t const& flags, void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			bool heap_free(mk::win::handle_t const& heap, mk::win::kernel32::heap_free_t const& flags, void* const& mem) noexcept;
			bool heap_destroy(mk::win::handle_t const& heap) noexcept;


		}
	}
}

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
				none                = 0x00000000,
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				enable_execute      = 0x00040000,
			};
			[[nodiscard]] inline mk::win::kernel32::heap_create_t operator|(mk::win::kernel32::heap_create_t const& a, mk::win::kernel32::heap_create_t const& b) noexcept { return static_cast<mk::win::kernel32::heap_create_t>(static_cast<mk::stdlib::uint32_t>(a) | static_cast<mk::stdlib::uint32_t>(b)); }

			enum class heap_alloc_t : mk::stdlib::uint32_t
			{
				none                = 0x00000000,
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				zero_memory         = 0x00000008,
			};
			[[nodiscard]] inline mk::win::kernel32::heap_alloc_t operator|(mk::win::kernel32::heap_alloc_t const& a, mk::win::kernel32::heap_alloc_t const& b) noexcept { return static_cast<mk::win::kernel32::heap_alloc_t>(static_cast<mk::stdlib::uint32_t>(a) | static_cast<mk::stdlib::uint32_t>(b)); }

			enum class heap_size_t
			{
				none         = 0x00000000,
				no_serialize = 0x00000001,
			};

			enum class heap_realloc_t : mk::stdlib::uint32_t
			{
				none                = 0x00000000,
				no_serialize        = 0x00000001,
				generate_exceptions = 0x00000004,
				zero_memory         = 0x00000008,
				in_place_only       = 0x00000010,
			};
			[[nodiscard]] inline mk::win::kernel32::heap_realloc_t operator|(mk::win::kernel32::heap_realloc_t const& a, mk::win::kernel32::heap_realloc_t const& b) noexcept { return static_cast<mk::win::kernel32::heap_realloc_t>(static_cast<mk::stdlib::uint32_t>(a) | static_cast<mk::stdlib::uint32_t>(b)); }

			enum class heap_free_t : mk::stdlib::uint32_t
			{
				none         = 0x00000000,
				no_serialize = 0x00000001,
			};


			[[nodiscard]] mk::win::handle_t get_process_heap(void) noexcept;
			[[nodiscard]] mk::win::handle_t heap_create(mk::win::kernel32::heap_create_t const& options, mk::stdlib::size_t const& initial_size, mk::stdlib::size_t const& maximum_size) noexcept;
			[[nodiscard]] void* heap_alloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_alloc_t const& flags, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] mk::stdlib::size_t heap_size(mk::win::handle_t const& heap, mk::win::kernel32::heap_size_t const& flags, void const* const& mem) noexcept;
			[[nodiscard]] void* heap_realloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_realloc_t const& flags, void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] bool heap_free(mk::win::handle_t const& heap, mk::win::kernel32::heap_free_t const& flags, void* const& mem) noexcept;
			[[nodiscard]] bool heap_destroy(mk::win::handle_t const& heap) noexcept;


		}
	}
}

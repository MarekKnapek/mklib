#include "heap.hpp"


extern "C" [[nodiscard]] __declspec(dllimport) mk::win::handle_t __stdcall GetProcessHeap(void) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) mk::win::handle_t __stdcall HeapCreate(mk::stdlib::uint32_t, mk::stdlib::size_t, mk::stdlib::size_t) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) void* __stdcall HeapAlloc(mk::win::handle_t, mk::stdlib::uint32_t, mk::stdlib::size_t) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) mk::stdlib::size_t __stdcall HeapSize(mk::win::handle_t, mk::stdlib::uint32_t, void const*) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) void* __stdcall HeapReAlloc(mk::win::handle_t, mk::stdlib::uint32_t, void*, mk::stdlib::size_t) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) mk::win::bool_t __stdcall HeapFree(mk::win::handle_t, mk::stdlib::uint32_t, void*) noexcept;
extern "C" [[nodiscard]] __declspec(dllimport) mk::win::bool_t __stdcall HeapDestroy(mk::win::handle_t) noexcept;


[[nodiscard]] mk::win::handle_t mk::win::kernel32::get_process_heap(void) noexcept
{
	return GetProcessHeap();
}

[[nodiscard]] mk::win::handle_t mk::win::kernel32::heap_create(mk::win::kernel32::heap_create_t const& options, mk::stdlib::size_t const& initial_size, mk::stdlib::size_t const& maximum_size) noexcept
{
	return HeapCreate(static_cast<mk::stdlib::uint32_t>(options), initial_size, maximum_size);
}

[[nodiscard]] void* mk::win::kernel32::heap_alloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_alloc_t const& flags, mk::stdlib::size_t const& bytes) noexcept
{
	return HeapAlloc(heap, static_cast<mk::stdlib::uint32_t>(flags), bytes);
}

[[nodiscard]] mk::stdlib::size_t mk::win::kernel32::heap_size(mk::win::handle_t const& heap, mk::win::kernel32::heap_size_t const& flags, void const* const& mem) noexcept
{
	return HeapSize(heap, static_cast<mk::stdlib::uint32_t>(flags), mem);
}

[[nodiscard]] void* mk::win::kernel32::heap_realloc(mk::win::handle_t const& heap, mk::win::kernel32::heap_realloc_t const& flags, void* const& mem, mk::stdlib::size_t const& bytes) noexcept
{
	return HeapReAlloc(heap, static_cast<mk::stdlib::uint32_t>(flags), mem, bytes);
}

[[nodiscard]] bool mk::win::kernel32::heap_free(mk::win::handle_t const& heap, mk::win::kernel32::heap_free_t const& flags, void* const& mem) noexcept
{
	return HeapFree(heap, static_cast<mk::stdlib::uint32_t>(flags), mem) != 0;
}

[[nodiscard]] bool mk::win::kernel32::heap_destroy(mk::win::handle_t const& heap) noexcept
{
	return HeapDestroy(heap) != 0;
}

#include "../src/stdlib/ints.hpp"
#include "../src/stdlib/size.hpp"
#include "../src/stdlib/heap/heap_multi_threaded.hpp"
#include "../src/stdlib/heap/heap_process.hpp"
#include "../src/stdlib/heap/heap_single_threaded.hpp"
#include "../src/stdlib/heap/heap_type_erased.hpp"
#include "../src/stdlib/heap/heap_virtual.hpp"


int main()
{
	static_assert(sizeof(mk::stdlib::uint8_t) == 1);
	static_assert(sizeof(mk::stdlib::uint16_t) == 2);
	static_assert(sizeof(mk::stdlib::uint32_t) == 4);
	static_assert(sizeof(mk::stdlib::uint64_t) == 8);

	static_assert(sizeof(mk::stdlib::int8_t) == 1);
	static_assert(sizeof(mk::stdlib::int16_t) == 2);
	static_assert(sizeof(mk::stdlib::int32_t) == 4);
	static_assert(sizeof(mk::stdlib::int64_t) == 8);


	static_assert(sizeof(mk::stdlib::size_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::ptrdiff_t) == sizeof(void*));


	mk::stdlib::heap_multi_threaded_t heap_multi_threaded;
	mk::stdlib::heap_process_t heap_process;
	mk::stdlib::heap_single_threaded_t heap_single_threaded;

	{
		mk::stdlib::heap_type_erased_t heap{heap_single_threaded};
		void* mem = heap.alloc(42);
		heap.free(mem);
	}

	{
		mk::stdlib::heap_virtual_t heap = mk::stdlib::heap_virtual_t::make<mk::stdlib::heap_single_threaded_t>();
		void* mem = heap.alloc(42);
		heap.free(mem);
	}
}

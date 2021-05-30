#include "../src/stdlib/ints.hpp"
#include "../src/stdlib/size.hpp"
#include "../src/stdlib/heap/heap_multi_threaded.hpp"
#include "../src/stdlib/heap/heap_process.hpp"
#include "../src/stdlib/heap/heap_single_threaded.hpp"
#include "../src/stdlib/heap/heap_type_erased.hpp"
#include "../src/stdlib/heap/heap_virtual.hpp"

#include "../src/stdlib/ring_buffer.hpp"
#include "../src/stdlib/cstdlib.hpp"

#include "tests_bits_buffer.hpp"
#include "tests_bits_vector.hpp"
#include "tests_heap_multi_threaded.hpp"
#include "tests_heap_process.hpp"
#include "tests_heap_single_threaded.hpp"
#include "tests_ints.hpp"
#include "tests_ring_buffer.hpp"
#include "tests_size.hpp"
#include "tests_unique_ptr_multi.hpp"
#include "tests_unique_ptr_single.hpp"

#define _ALLOW_RTCc_IN_STL
#include <string>
#undef _ALLOW_RTCc_IN_STL

void bits_vector_tests();

int main()
{
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

	#if 0
	for(int j = 0; j != 100; ++j)
	{
		mk::stdlib::ring_buffer_t<std::string, 5> buff;
		for(int a = 0; a != j; ++a)
		{
			buff.push_back("========== 42 ========== ========== ========== ==========");
			buff.pop_front();
		}
		MK_STDLIB_ASSERT(buff.size() == 0);
		for(int i = 0; i != 100; ++i)
		{
			buff.push_back("========== 42 ========== ========== ========== ==========");
			buff.push_back("========== 43 ========== ========== ========== ==========");
			buff.push_back("========== 44 ========== ========== ========== ==========");
			MK_STDLIB_ASSERT(buff[0] == "========== 42 ========== ========== ========== ==========");
			MK_STDLIB_ASSERT(buff.size() == 3);
			MK_STDLIB_ASSERT(buff.first_half().size() + buff.second_half().size() == 3);
			buff.pop_front();
			buff.pop_front();
			buff.pop_front();
		}
		buff.push_back("========== 42 ========== ========== ========== ==========");
		buff.push_back("========== 43 ========== ========== ========== ==========");
		buff.push_back("========== 44 ========== ========== ========== ==========");
		auto copied = buff;
		auto moved = mk::stdlib::move(copied);
	}
	#endif

	mk::stdlib::cstdlib_init_t const stdlib;

	test_heap_multi_threaded::test();
	test_heap_process::test();
	test_heap_single_threaded::test();
	tests_bits_buffer::test();
	tests_bits_vector::test();
	tests_ints::test();
	tests_ring_buffer::test();
	tests_size::test();
	tests_unique_ptr_multi::test();
	tests_unique_ptr_single::test();

	return 0;
}

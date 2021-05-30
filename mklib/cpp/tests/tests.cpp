#include "../src/stdlib/cstdlib.hpp"
#include "tests_bits_buffer.hpp"
#include "tests_bits_vector.hpp"
#include "tests_heap_multi_threaded.hpp"
#include "tests_heap_process.hpp"
#include "tests_heap_single_threaded.hpp"
#include "tests_heap_type_erased.hpp"
#include "tests_ints.hpp"
#include "tests_ring_buffer.hpp"
#include "tests_size.hpp"
#include "tests_unique_ptr_multi.hpp"
#include "tests_unique_ptr_single.hpp"


int main()
{
	mk::stdlib::cstdlib_init_t const stdlib;

	tests_bits_buffer::tests();
	tests_bits_vector::tests();
	tests_heap_multi_threaded::tests();
	tests_heap_process::tests();
	tests_heap_single_threaded::tests();
	tests_heap_type_erased::tests();
	tests_ints::tests();
	tests_ring_buffer::tests();
	tests_size::tests();
	tests_unique_ptr_multi::tests();
	tests_unique_ptr_single::tests();

	return 0;
}

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


int main()
{
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

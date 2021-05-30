#include "tests_heap_process.hpp"
#include "../src/stdlib/heap/heap_process.hpp"

#include "../src/stdlib/utility/move.hpp"
#include "../src/stdlib/ints.hpp"
#include "../src/stdlib/verify.hpp"


namespace tests_heap_process
{
	namespace impl
	{
		void test_default_construct();
		void test_move_construct();
		void test_move_assign();
		void test_swap_member();
		void test_swap_nonmember();
		void test_alloc();
		void test_size();
		void test_realloc();
		void test_realloc_inplace();
	}
}


void tests_heap_process::tests()
{
	tests_heap_process::impl::test_default_construct();
	tests_heap_process::impl::test_move_construct();
	tests_heap_process::impl::test_move_assign();
	tests_heap_process::impl::test_swap_member();
	tests_heap_process::impl::test_swap_nonmember();
	tests_heap_process::impl::test_alloc();
	tests_heap_process::impl::test_size();
	tests_heap_process::impl::test_realloc();
	tests_heap_process::impl::test_realloc_inplace();
}


void tests_heap_process::impl::test_default_construct()
{
	mk::stdlib::heap_process_t heap;

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get());
}

void tests_heap_process::impl::test_move_construct()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();

	mk::stdlib::heap_process_t heap_2 = mk::stdlib::move(heap);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get());
}

void tests_heap_process::impl::test_move_assign()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
	mk::stdlib::heap_process_t heap_2;

	heap_2 = mk::stdlib::move(heap);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get());
}

void tests_heap_process::impl::test_swap_member()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
	mk::stdlib::heap_process_t heap_2;

	heap.swap(heap_2);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get());
}

void tests_heap_process::impl::test_swap_nonmember()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
	mk::stdlib::heap_process_t heap_2;

	swap(heap, heap_2);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get());
}

void tests_heap_process::impl::test_alloc()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();

	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));

	MK_STDLIB_VERIFY(p_num);
	*p_num = 0x1234567890abcdefull;
	heap.free(p_num);
}

void tests_heap_process::impl::test_size()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));

	mk::stdlib::size_t const size = heap.size(p_num);

	MK_STDLIB_VERIFY(size >= sizeof(mk::stdlib::uint64_t));
	heap.free(p_num);
}

void tests_heap_process::impl::test_realloc()
{
	mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));
	*p_num = 0x1234567890abcdefull;

	mk::stdlib::uint64_t* const p_new_num = static_cast<mk::stdlib::uint64_t*>(heap.realloc(p_num, 1 * 1024 * 1024));

	MK_STDLIB_VERIFY(*p_new_num == 0x1234567890abcdefull);
	heap.free(p_new_num);
}

void tests_heap_process::impl::test_realloc_inplace()
{
	static constexpr int const s_new_sizes[] = {16, 1 * 1024 * 1024};

	for(auto const& new_size : s_new_sizes)
	{
		mk::stdlib::heap_process_t heap = mk::stdlib::heap_process_t::make();
		mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));
		*p_num = 0x1234567890abcdefull;

		mk::stdlib::uint64_t* const p_new_num = static_cast<mk::stdlib::uint64_t*>(heap.realloc_inplace(p_num, new_size));

		MK_STDLIB_VERIFY(!p_new_num || p_new_num == p_num);
		heap.free(p_num);
	}
}

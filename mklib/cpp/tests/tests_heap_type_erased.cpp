#include "tests_heap_type_erased.hpp"
#include "../src/stdlib/heap/heap_type_erased.hpp"

#include "../src/stdlib/heap/heap_multi_threaded.hpp"
#include "../src/stdlib/heap/heap_process.hpp"
#include "../src/stdlib/heap/heap_single_threaded.hpp"
#include "../src/stdlib/ints.hpp"
#include "../src/stdlib/utility/move.hpp"
#include "../src/stdlib/verify.hpp"


namespace tests_heap_type_erased
{
	namespace impl
	{
		template<typename t> void tests();
		template<typename t> void test_default_construct();
		template<typename t> void test_copy_construct();
		template<typename t> void test_move_construct();
		template<typename t> void test_copy_assign();
		template<typename t> void test_move_assign();
		template<typename t> void test_swap_member();
		template<typename t> void test_swap_nonmember();
		template<typename t> void test_alloc();
		template<typename t> void test_size();
		template<typename t> void test_realloc();
		template<typename t> void test_realloc_inplace();
	}
}


void tests_heap_type_erased::tests()
{
	tests_heap_type_erased::impl::tests<mk::stdlib::heap_multi_threaded_t>();
	tests_heap_type_erased::impl::tests<mk::stdlib::heap_process_t>();
	tests_heap_type_erased::impl::tests<mk::stdlib::heap_single_threaded_t>();
}


template<typename t>
void tests_heap_type_erased::impl::tests()
{
	tests_heap_type_erased::impl::test_default_construct<t>();
	tests_heap_type_erased::impl::test_copy_construct<t>();
	tests_heap_type_erased::impl::test_move_construct<t>();
	tests_heap_type_erased::impl::test_copy_assign<t>();
	tests_heap_type_erased::impl::test_move_assign<t>();
	tests_heap_type_erased::impl::test_swap_member<t>();
	tests_heap_type_erased::impl::test_swap_nonmember<t>();
	tests_heap_type_erased::impl::test_alloc<t>();
	tests_heap_type_erased::impl::test_size<t>();
	tests_heap_type_erased::impl::test_realloc<t>();
	tests_heap_type_erased::impl::test_realloc_inplace<t>();
}

template<typename t>
void tests_heap_type_erased::impl::test_default_construct()
{
	mk::stdlib::heap_type_erased_t heap;

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get_heap());
}

template<typename t>
void tests_heap_type_erased::impl::test_copy_construct()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};

	mk::stdlib::heap_type_erased_t heap_2 = heap;

	MK_STDLIB_VERIFY(heap);
	MK_STDLIB_VERIFY(heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_heap() == heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_type() == heap_2.get_type());
}

template<typename t>
void tests_heap_type_erased::impl::test_move_construct()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};

	mk::stdlib::heap_type_erased_t heap_2 = mk::stdlib::move(heap);

	MK_STDLIB_VERIFY(heap);
	MK_STDLIB_VERIFY(heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_heap() == heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_type() == heap_2.get_type());
}

template<typename t>
void tests_heap_type_erased::impl::test_copy_assign()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::heap_type_erased_t heap_2;

	heap_2 = heap;

	MK_STDLIB_VERIFY(heap);
	MK_STDLIB_VERIFY(heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_heap() == heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_type() == heap_2.get_type());
}

template<typename t>
void tests_heap_type_erased::impl::test_move_assign()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::heap_type_erased_t heap_2;

	heap_2 = mk::stdlib::move(heap);

	MK_STDLIB_VERIFY(heap);
	MK_STDLIB_VERIFY(heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_heap() == heap_2.get_heap());
	MK_STDLIB_VERIFY(heap.get_type() == heap_2.get_type());
}

template<typename t>
void tests_heap_type_erased::impl::test_swap_member()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::heap_type_erased_t heap_2;

	heap.swap(heap_2);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
}

template<typename t>
void tests_heap_type_erased::impl::test_swap_nonmember()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::heap_type_erased_t heap_2;

	swap(heap, heap_2);

	MK_STDLIB_VERIFY(!heap);
	MK_STDLIB_VERIFY(!heap.get_heap());
	MK_STDLIB_VERIFY(heap_2);
	MK_STDLIB_VERIFY(heap_2.get_heap());
}

template<typename t>
void tests_heap_type_erased::impl::test_alloc()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};

	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));

	MK_STDLIB_VERIFY(p_num);
	*p_num = 0x1234567890abcdefull;
	heap.free(p_num);
}

template<typename t>
void tests_heap_type_erased::impl::test_size()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));

	mk::stdlib::size_t const size = heap.size(p_num);

	MK_STDLIB_VERIFY(size >= sizeof(mk::stdlib::uint64_t));
	heap.free(p_num);
}

template<typename t>
void tests_heap_type_erased::impl::test_realloc()
{
	t h = t::make();
	mk::stdlib::heap_type_erased_t heap{h};
	mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));
	*p_num = 0x1234567890abcdefull;

	mk::stdlib::uint64_t* const p_new_num = static_cast<mk::stdlib::uint64_t*>(heap.realloc(p_num, 1 * 1024 * 1024));

	MK_STDLIB_VERIFY(*p_new_num == 0x1234567890abcdefull);
	heap.free(p_new_num);
}

template<typename t>
void tests_heap_type_erased::impl::test_realloc_inplace()
{
	static constexpr int const s_new_sizes[] = {16, 1 * 1024 * 1024};

	for(auto const& new_size : s_new_sizes)
	{
		t h = t::make();
		mk::stdlib::heap_type_erased_t heap{h};
		mk::stdlib::uint64_t* const p_num = static_cast<mk::stdlib::uint64_t*>(heap.alloc(sizeof(mk::stdlib::uint64_t)));
		*p_num = 0x1234567890abcdefull;

		mk::stdlib::uint64_t* const p_new_num = static_cast<mk::stdlib::uint64_t*>(heap.realloc_inplace(p_num, new_size));

		MK_STDLIB_VERIFY(!p_new_num || p_new_num == p_num);
		heap.free(p_num);
	}
}

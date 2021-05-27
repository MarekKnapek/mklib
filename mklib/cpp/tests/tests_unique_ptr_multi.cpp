#include "tests_unique_ptr_multi.hpp"
#include "../src/stdlib/memory/unique_ptr_multi.hpp"

#include "../src/stdlib/assert.hpp" // MK_STDLIB_ASSERT
#include "../src/stdlib/utility/move.hpp" // mk::stdlib::move


namespace tests_unique_ptr_multi
{
	namespace impl
	{
		static constexpr int const s_count = 10;
		template<typename t>
		void test();
	}
}


void tests_unique_ptr_multi::test()
{
	tests_unique_ptr_multi::impl::test<int>();
	tests_unique_ptr_multi::impl::test<mk::stdlib::unique_ptr_t<int[]>>();
}


template<typename t>
void tests_unique_ptr_multi::impl::test()
{
	{
		mk::stdlib::unique_ptr_t<t[]> up;

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
	}
	{
		mk::stdlib::unique_ptr_t<t[]> up = mk::stdlib::make_unique<t[]>(tests_unique_ptr_multi::impl::s_count);

		MK_STDLIB_ASSERT(up.get());
		MK_STDLIB_ASSERT(up);
		MK_STDLIB_ASSERT(&up[0]);
	}
	{
		mk::stdlib::unique_ptr_t<t[]> up = mk::stdlib::make_unique<t[]>(tests_unique_ptr_multi::impl::s_count);

		mk::stdlib::unique_ptr_t<t[]> up2{mk::stdlib::move(up)};

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get());
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(&up2[0]);
	}
	{
		mk::stdlib::unique_ptr_t<t[]> up = mk::stdlib::make_unique<t[]>(tests_unique_ptr_multi::impl::s_count);

		mk::stdlib::unique_ptr_t<t[]> up2;
		up2 = mk::stdlib::move(up);

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get());
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(&up2[0]);
	}
	{
		mk::stdlib::unique_ptr_t<t[]> a{reinterpret_cast<t*>(0x10)};
		mk::stdlib::unique_ptr_t<t[]> b{reinterpret_cast<t*>(0x20)};

		using mk::stdlib::swap;
		swap(a, b);

		MK_STDLIB_ASSERT(a.get() == reinterpret_cast<t*>(0x20));
		MK_STDLIB_ASSERT(b.get() == reinterpret_cast<t*>(0x10));
		MK_STDLIB_ASSERT(a.release() == reinterpret_cast<t*>(0x20));
		MK_STDLIB_ASSERT(b.release() == reinterpret_cast<t*>(0x10));
	}
}

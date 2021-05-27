#include "tests_unique_ptr_single.hpp"
#include "../src/stdlib/memory/unique_ptr_single.hpp"

#include "../src/stdlib/assert.hpp" // MK_STDLIB_ASSERT
#include "../src/stdlib/utility/move.hpp" // mk::stdlib::move


namespace tests_unique_ptr_single
{
	namespace impl
	{
		template<typename t>
		void test();
	}
}


void tests_unique_ptr_single::test()
{
	tests_unique_ptr_single::impl::test<int>();
	tests_unique_ptr_single::impl::test<mk::stdlib::unique_ptr_t<int>>();
}


template<typename t>
void tests_unique_ptr_single::impl::test()
{
	{
		mk::stdlib::unique_ptr_t<t> up;

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
	}
	{
		mk::stdlib::unique_ptr_t<t> up = mk::stdlib::make_unique<t>();

		MK_STDLIB_ASSERT(up.get());
		MK_STDLIB_ASSERT(up);
		MK_STDLIB_ASSERT(&*up);
	}
	{
		mk::stdlib::unique_ptr_t<t> up = mk::stdlib::make_unique<t>();

		mk::stdlib::unique_ptr_t<t> up2{mk::stdlib::move(up)};

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get());
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(&*up2);
	}
	{
		mk::stdlib::unique_ptr_t<t> up = mk::stdlib::make_unique<t>();

		mk::stdlib::unique_ptr_t<t> up2;
		up2 = mk::stdlib::move(up);

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get());
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(&*up2);
	}
	{
		mk::stdlib::unique_ptr_t<t> a{reinterpret_cast<t*>(0x10)};
		mk::stdlib::unique_ptr_t<t> b{reinterpret_cast<t*>(0x20)};

		using mk::stdlib::swap;
		swap(a, b);

		MK_STDLIB_ASSERT(a.get() == reinterpret_cast<t*>(0x20));
		MK_STDLIB_ASSERT(b.get() == reinterpret_cast<t*>(0x10));
		MK_STDLIB_ASSERT(a.release() == reinterpret_cast<t*>(0x20));
		MK_STDLIB_ASSERT(b.release() == reinterpret_cast<t*>(0x10));
	}
}

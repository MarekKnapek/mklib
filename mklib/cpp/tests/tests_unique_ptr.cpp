#include "tests_unique_ptr.hpp"
#include "../src/stdlib/memory/unique_ptr.hpp"

#include "../src/stdlib/cstdlib.hpp" // malloc
#include "../src/stdlib/assert.hpp" // MK_STDLIB_ASSERT
#include "../src/stdlib/utility/move.hpp" // move


void tests_unique_ptr::test()
{
	{
		mk::stdlib::unique_ptr_t<int> up;

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
	}
	{
		mk::stdlib::unique_ptr_t<int[]> up;

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
	}
	{
		int* const int_ptr = static_cast<int*>(mk::stdlib::malloc(sizeof(int)));
		*int_ptr = 42;
		mk::stdlib::unique_ptr_t<int> up{int_ptr};

		MK_STDLIB_ASSERT(up.get() == int_ptr);
		MK_STDLIB_ASSERT(up);
		MK_STDLIB_ASSERT(*up == 42);
	}
	{
		int* const ints_ptr = static_cast<int*>(mk::stdlib::malloc(5 * sizeof(int)));
		ints_ptr[0] = 42;
		ints_ptr[1] = 43;
		ints_ptr[2] = 44;
		ints_ptr[3] = 45;
		ints_ptr[4] = 46;
		mk::stdlib::unique_ptr_t<int[]> up{ints_ptr};

		MK_STDLIB_ASSERT(up.get() == ints_ptr);
		MK_STDLIB_ASSERT(up);
		MK_STDLIB_ASSERT(up[0] == 42);
		MK_STDLIB_ASSERT(up[1] == 43);
		MK_STDLIB_ASSERT(up[2] == 44);
		MK_STDLIB_ASSERT(up[3] == 45);
		MK_STDLIB_ASSERT(up[4] == 46);
	}
	{
		int* const int_ptr = static_cast<int*>(mk::stdlib::malloc(sizeof(int)));
		*int_ptr = 42;
		mk::stdlib::unique_ptr_t<int> up{int_ptr};

		mk::stdlib::unique_ptr_t<int> up2{mk::stdlib::move(up)};

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get() == int_ptr);
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(*up2 == 42);
	}
	{
		int* const ints_ptr = static_cast<int*>(mk::stdlib::malloc(5 * sizeof(int)));
		ints_ptr[0] = 42;
		ints_ptr[1] = 43;
		ints_ptr[2] = 44;
		ints_ptr[3] = 45;
		ints_ptr[4] = 46;
		mk::stdlib::unique_ptr_t<int[]> up{ints_ptr};

		mk::stdlib::unique_ptr_t<int[]> up2{mk::stdlib::move(up)};

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get() == ints_ptr);
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(up2[0] == 42);
		MK_STDLIB_ASSERT(up2[1] == 43);
		MK_STDLIB_ASSERT(up2[2] == 44);
		MK_STDLIB_ASSERT(up2[3] == 45);
		MK_STDLIB_ASSERT(up2[4] == 46);
	}
	{
		int* const int_ptr = static_cast<int*>(mk::stdlib::malloc(sizeof(int)));
		*int_ptr = 42;
		mk::stdlib::unique_ptr_t<int> up{int_ptr};

		mk::stdlib::unique_ptr_t<int> up2;
		up2 = mk::stdlib::move(up);

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get() == int_ptr);
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(*up2 == 42);
	}
	{
		int* const ints_ptr = static_cast<int*>(mk::stdlib::malloc(5 * sizeof(int)));
		ints_ptr[0] = 42;
		ints_ptr[1] = 43;
		ints_ptr[2] = 44;
		ints_ptr[3] = 45;
		ints_ptr[4] = 46;
		mk::stdlib::unique_ptr_t<int[]> up{ints_ptr};

		mk::stdlib::unique_ptr_t<int[]> up2;
		up2 = mk::stdlib::move(up);

		MK_STDLIB_ASSERT(up.get() == nullptr);
		MK_STDLIB_ASSERT(!up);
		MK_STDLIB_ASSERT(up2.get() == ints_ptr);
		MK_STDLIB_ASSERT(up2);
		MK_STDLIB_ASSERT(up2[0] == 42);
		MK_STDLIB_ASSERT(up2[1] == 43);
		MK_STDLIB_ASSERT(up2[2] == 44);
		MK_STDLIB_ASSERT(up2[3] == 45);
		MK_STDLIB_ASSERT(up2[4] == 46);
	}
	{
		mk::stdlib::unique_ptr_t<int> a{reinterpret_cast<int*>(0x1)};
		mk::stdlib::unique_ptr_t<int> b{reinterpret_cast<int*>(0x2)};

		mk::stdlib::swap(a, b);

		MK_STDLIB_ASSERT(a.get() == reinterpret_cast<int*>(0x2));
		MK_STDLIB_ASSERT(b.get() == reinterpret_cast<int*>(0x1));
		MK_STDLIB_ASSERT(a.release() == reinterpret_cast<int*>(0x2));
		MK_STDLIB_ASSERT(b.release() == reinterpret_cast<int*>(0x1));
	}
	{
		mk::stdlib::unique_ptr_t<int[]> a{reinterpret_cast<int*>(0x1)};
		mk::stdlib::unique_ptr_t<int[]> b{reinterpret_cast<int*>(0x2)};

		mk::stdlib::swap(a, b);

		MK_STDLIB_ASSERT(a.get() == reinterpret_cast<int*>(0x2));
		MK_STDLIB_ASSERT(b.get() == reinterpret_cast<int*>(0x1));
		MK_STDLIB_ASSERT(a.release() == reinterpret_cast<int*>(0x2));
		MK_STDLIB_ASSERT(b.release() == reinterpret_cast<int*>(0x1));
	}
}

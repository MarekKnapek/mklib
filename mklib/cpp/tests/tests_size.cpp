#include "tests_size.hpp"
#include "../src/stdlib/size.hpp"


void tests_size::tests()
{
	static_assert(sizeof(mk::stdlib::size_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::ptrdiff_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::uintptr_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::intptr_t) == sizeof(void*));
}

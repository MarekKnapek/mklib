#include "tests_size.hpp"
#include "../src/stdlib/size.hpp"


void tests_size::test()
{
	static_assert(sizeof(mk::stdlib::size_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::ptrdiff_t) == sizeof(void*));
}
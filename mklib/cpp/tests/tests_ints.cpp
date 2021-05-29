#include "tests_ints.hpp"
#include "../src/stdlib/ints.hpp"


void tests_ints::test()
{
	static_assert(sizeof(mk::stdlib::uint8_t) == 1);
	static_assert(sizeof(mk::stdlib::uint16_t) == 2);
	static_assert(sizeof(mk::stdlib::uint32_t) == 4);
	static_assert(sizeof(mk::stdlib::uint64_t) == 8);

	static_assert(sizeof(mk::stdlib::int8_t) == 1);
	static_assert(sizeof(mk::stdlib::int16_t) == 2);
	static_assert(sizeof(mk::stdlib::int32_t) == 4);
	static_assert(sizeof(mk::stdlib::int64_t) == 8);
}

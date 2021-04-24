#include "../src/stdlib/ints.hpp"
#include "../src/stdlib/size.hpp"


int main()
{
	static_assert(sizeof(mk::stdlib::uint8_t) == 1);
	static_assert(sizeof(mk::stdlib::uint16_t) == 2);
	static_assert(sizeof(mk::stdlib::uint32_t) == 4);
	static_assert(sizeof(mk::stdlib::uint64_t) == 8);

	static_assert(sizeof(mk::stdlib::int8_t) == 1);
	static_assert(sizeof(mk::stdlib::int16_t) == 2);
	static_assert(sizeof(mk::stdlib::int32_t) == 4);
	static_assert(sizeof(mk::stdlib::int64_t) == 8);


	static_assert(sizeof(mk::stdlib::size_t) == sizeof(void*));
	static_assert(sizeof(mk::stdlib::ptrdiff_t) == sizeof(void*));
}

#include "tests_bits_buffer.hpp"
#include "../src/stdlib/bits_vector/bits_buffer.hpp"

#include "../src/stdlib/assert.hpp"

namespace tests_bits_buffer
{


	enum class olympic_medal
	{
		gold,
		silver,
		bronze,
		potato,
	};


}


void tests_bits_buffer::test()
{
	mk::stdlib::bits_buffer_t<olympic_medal, 2> buff(1'000);
	buff[42] = olympic_medal::bronze;

	MK_STDLIB_ASSERT(buff[42] == olympic_medal::bronze);
}

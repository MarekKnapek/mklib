#include "tests_bits_vector.hpp"
#include "../src/stdlib/bits_vector/bits_vector.hpp"

#include "../src/stdlib/assert.hpp"


namespace tests_bits_vector
{

	enum class olympic_medal_t
	{
		gold,
		silver,
		bronze,
		potato,
	};

}


void tests_bits_vector::test()
{
	{
		// default construct
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec;
		MK_STDLIB_ASSERT(vec.empty());
	}
	{
		// size construct
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec{1'000};
		MK_STDLIB_ASSERT(!vec.empty());
	}
	{
		// copy construct
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec{1'000};
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec2{vec};
		MK_STDLIB_ASSERT(vec2.size() == 1'000);
	}
	{
		// iterator
		mk::stdlib::bits_vector_t<int, 2> vec{1'000};
		auto it = vec.cbegin();
		++it;
		auto it2 = vec.begin();
		++it2;
		MK_STDLIB_ASSERT(it == it2);
	}
	{
		// reference
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec;
		vec.resize(64);
		vec[42] = olympic_medal_t::potato;
		static_cast<mk::stdlib::bits_vector_t<olympic_medal_t, 2> const&>(vec)[0] = vec[42];
		MK_STDLIB_ASSERT(vec[0] == olympic_medal_t::potato);
	}
}

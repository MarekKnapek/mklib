#include "tests_bits_vector.hpp"
#include "../src/stdlib/bits_vector/bits_vector.hpp"

#include "../src/stdlib/algorithm.hpp"
#include "../src/stdlib/assert.hpp"


namespace tests_bits_vector
{

	enum class olympic_medal_t : unsigned char
	{
		gold,
		silver,
		bronze,
		potato,
	};

}


void tests_bits_vector::tests()
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
		vec[0] = vec[42];
		MK_STDLIB_ASSERT(vec[0] == olympic_medal_t::potato);
	}
	{
		// iterator
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec;
		vec.resize(64);
		vec[42] = olympic_medal_t::potato;
		mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec2;
		vec2.resize(64);
		mk::stdlib::copy(vec.cbegin(), vec.cend(), vec2.begin());
		for(int i = 0; i != 64; ++i)
		{
			MK_STDLIB_ASSERT(vec[i] == vec2[i]);
		}
	}
	{
		// resize
		for(int i_size = 0; i_size != 1'000; ++i_size)
		{
			mk::stdlib::bits_vector_t<olympic_medal_t, 2> vec;
			vec.resize(i_size);
			mk::stdlib::fill(vec.begin(), vec.cend(), olympic_medal_t::potato);
			vec.push_back(olympic_medal_t::silver);
			vec.pop_back();
			vec.resize(2'000);
			for(int i = 0; i != i_size; ++i)
			{
				MK_STDLIB_ASSERT(vec[i] == olympic_medal_t::potato);
			}
			for(int i = i_size; i != 2'000; ++i)
			{
				MK_STDLIB_ASSERT(vec[i] == olympic_medal_t{});
			}
		}
	}
}

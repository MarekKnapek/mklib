#if 0
#include "../src/stdlib/bits_vector/bits_vector.hpp"

#include "../src/stdlib/assert.hpp"
#include "../src/stdlib/cstdlib.hpp"

#define _ALLOW_RTCc_IN_STL
#include <random>
#include <vector>
#undef _ALLOW_RTCc_IN_STL


enum class olympic_medal
{
	gold,
	silver,
	bronze,
	potato,
};


void bits_vector_tests()
{
	/**
	 *
	 * Create two vectors, one compressed one standard.
	 * Resize both to the same size.
	 *
	 * Repeat many times:
	 *   Change approximately half of elements to random value.
	 *   Check that both vectors contain the same values.
	 *
	 */

	int const n_repeats = 1'000;
	int const n_elements = 1'000;
	int const n_rewrites = 500;

	mk::stdlib::cstdlib_init();
	{
		mk::stdlib::bits_vector_t<olympic_medal, 2> vec_bts;
		std::vector<olympic_medal> vec_std;
		vec_bts.resize(n_elements);
		vec_std.resize(n_elements);

		std::default_random_engine eng{std::random_device{}()};
		std::uniform_int_distribution<int> dst_val{0, 3};
		std::uniform_int_distribution<int> dst_idx{0, n_elements - 1};

		for(int i_repeat = 0; i_repeat != n_repeats; ++i_repeat)
		{
			for(int i_rewrites = 0; i_rewrites != n_rewrites; ++i_rewrites)
			{
				int const rnd_idx = dst_idx(eng);
				int const rnd_int = dst_val(eng);
				olympic_medal const rnd_val = static_cast<olympic_medal>(rnd_int);

				vec_bts[rnd_idx] = rnd_val;
				vec_std[rnd_idx] = rnd_val;
			}

			for(int i = 0; i != n_elements; ++i)
			{
				olympic_medal const val_bits = vec_bts[i];
				olympic_medal const val_std = vec_std[i];
				MK_STDLIB_ASSERT(val_bits == val_std);
			}
		}
	}
	{
		mk::stdlib::bits_vector_t<olympic_medal, 2> vec_bts;
		std::vector<olympic_medal> vec_std;

		std::default_random_engine eng{std::random_device{}()};
		std::uniform_int_distribution<int> dst_val{0, 3};
		std::uniform_int_distribution<int> dst_idx{0, n_elements - 1};

		for(int i_repeat = 0; i_repeat != 10; ++i_repeat)
		{
			for(int i_rewrites = 0; i_rewrites != n_rewrites; ++i_rewrites)
			{
				int const rnd_int = dst_val(eng);
				olympic_medal const rnd_val = static_cast<olympic_medal>(rnd_int);

				vec_bts.push_back(rnd_val);
				vec_std.push_back(rnd_val);

				MK_STDLIB_ASSERT(vec_bts.size() == vec_std.size());
				for(mk::stdlib::size_t i = 0; i != vec_bts.size(); ++i)
				{
					olympic_medal const val_bits = vec_bts[i];
					olympic_medal const val_std = vec_std[i];
					MK_STDLIB_ASSERT(val_bits == val_std);
				}
			}
		}
	}
	{
		mk::stdlib::bits_vector_t<olympic_medal, 2> b;
		b.push_back(olympic_medal::potato);
		b.push_back(olympic_medal::potato);
		b.pop_back();
		b.resize(2);
		MK_STDLIB_ASSERT(b[1] == olympic_medal{});
	}
	mk::stdlib::cstdlib_deinit();
}
#endif

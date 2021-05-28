#include "tests_ring_buffer.hpp"
#include "../src/stdlib/ring_buffer.hpp"

#include "../src/stdlib/assert.hpp" // MK_STDLIB_ASSERT
#include "../src/stdlib/memory/unique_ptr.hpp" // mk::stdlib::unique_ptr_t
#include "../src/stdlib/type_traits/is_trivial.hpp" // mk::stdlib::is_trivial_t


namespace tests_ring_buffer
{
	namespace impl
	{
		template<typename t>
		void test();
	}
}


void tests_ring_buffer::test()
{
	tests_ring_buffer::impl::test<int>();
	tests_ring_buffer::impl::test<mk::stdlib::unique_ptr_t<int>>();
	tests_ring_buffer::impl::test<mk::stdlib::unique_ptr_t<int[]>>();
}


template<typename t>
void tests_ring_buffer::impl::test()
{
	{
		mk::stdlib::ring_buffer_t<t, 5> buff;

		MK_STDLIB_ASSERT(buff.empty() == true);
		MK_STDLIB_ASSERT(buff.full() == false);
		MK_STDLIB_ASSERT(buff.size() == 0);
		MK_STDLIB_ASSERT(buff.capacity() == 8);
		MK_STDLIB_ASSERT(buff.free() == 8);
		MK_STDLIB_ASSERT(buff.first_half().size() == 0);
		MK_STDLIB_ASSERT(buff.second_half().size() == 0);
	}
	{
		for(int i = 0; i != 100; ++i)
		{
			mk::stdlib::ring_buffer_t<t, 5> buff;
			buff.push_back(t{});
			buff.push_back(t{});
			for(int j = 0; j != i; ++j)
			{
				buff.pop_front();
				buff.push_back(t{});
			}
			MK_STDLIB_ASSERT(buff.empty() == false);
			MK_STDLIB_ASSERT(buff.full() == false);
			MK_STDLIB_ASSERT(buff.size() == 2);
			MK_STDLIB_ASSERT(buff.capacity() == 8);
			MK_STDLIB_ASSERT(buff.free() == 6);
			MK_STDLIB_ASSERT(buff.first_half().size() + buff.second_half().size() == 2);
			MK_STDLIB_ASSERT(buff[0] == t{});
			MK_STDLIB_ASSERT(buff[1] == t{});
		}
	}
	if constexpr(mk::stdlib::is_trivial_t<t>::s_value)
	{
		for(int i = 0; i != 100; ++i)
		{
			mk::stdlib::ring_buffer_t<t, 5> buff;
			buff.push_back(t{});
			buff.push_back(t{});
			for(int j = 0; j != i; ++j)
			{
				buff.pop_front();
				buff.push_back(t{});
			}

			mk::stdlib::ring_buffer_t<t, 5> buff_2 = buff;

			MK_STDLIB_ASSERT(buff.empty() == false);
			MK_STDLIB_ASSERT(buff.full() == false);
			MK_STDLIB_ASSERT(buff.size() == 2);
			MK_STDLIB_ASSERT(buff.capacity() == 8);
			MK_STDLIB_ASSERT(buff.free() == 6);
			MK_STDLIB_ASSERT(buff.first_half().size() + buff.second_half().size() == 2);
			MK_STDLIB_ASSERT(buff[0] == t{});
			MK_STDLIB_ASSERT(buff[1] == t{});

			MK_STDLIB_ASSERT(buff_2.empty() == false);
			MK_STDLIB_ASSERT(buff_2.full() == false);
			MK_STDLIB_ASSERT(buff_2.size() == 2);
			MK_STDLIB_ASSERT(buff_2.capacity() == 8);
			MK_STDLIB_ASSERT(buff_2.free() == 6);
			MK_STDLIB_ASSERT(buff_2.first_half().size() == 2);
			MK_STDLIB_ASSERT(buff_2.first_half()[0] == t{});
			MK_STDLIB_ASSERT(buff_2.first_half()[1] == t{});
			MK_STDLIB_ASSERT(buff_2.second_half().size() == 0);
			MK_STDLIB_ASSERT(buff_2[0] == t{});
			MK_STDLIB_ASSERT(buff_2[1] == t{});
		}
	}
	if constexpr(mk::stdlib::is_trivial_t<t>::s_value)
	{
		for(int i = 0; i != 100; ++i)
		{
			mk::stdlib::ring_buffer_t<t, 5> buff;
			buff.push_back(t{});
			buff.push_back(t{});
			for(int j = 0; j != i; ++j)
			{
				buff.pop_front();
				buff.push_back(t{});
			}

			mk::stdlib::ring_buffer_t<t, 5> buff_2;
			buff_2 = buff;

			MK_STDLIB_ASSERT(buff.empty() == false);
			MK_STDLIB_ASSERT(buff.full() == false);
			MK_STDLIB_ASSERT(buff.size() == 2);
			MK_STDLIB_ASSERT(buff.capacity() == 8);
			MK_STDLIB_ASSERT(buff.free() == 6);
			MK_STDLIB_ASSERT(buff.first_half().size() + buff.second_half().size() == 2);
			MK_STDLIB_ASSERT(buff[0] == t{});
			MK_STDLIB_ASSERT(buff[1] == t{});

			MK_STDLIB_ASSERT(buff_2.empty() == false);
			MK_STDLIB_ASSERT(buff_2.full() == false);
			MK_STDLIB_ASSERT(buff_2.size() == 2);
			MK_STDLIB_ASSERT(buff_2.capacity() == 8);
			MK_STDLIB_ASSERT(buff_2.free() == 6);
			MK_STDLIB_ASSERT(buff_2.first_half().size() == 2);
			MK_STDLIB_ASSERT(buff_2.first_half()[0] == t{});
			MK_STDLIB_ASSERT(buff_2.first_half()[1] == t{});
			MK_STDLIB_ASSERT(buff_2.second_half().size() == 0);
			MK_STDLIB_ASSERT(buff_2[0] == t{});
			MK_STDLIB_ASSERT(buff_2[1] == t{});
		}
	}
	{
		for(int i = 0; i != 100; ++i)
		{
			mk::stdlib::ring_buffer_t<t, 5> buff;
			buff.push_back(t{});
			buff.push_back(t{});
			for(int j = 0; j != i; ++j)
			{
				buff.pop_front();
				buff.push_back(t{});
			}
			
			mk::stdlib::ring_buffer_t<t, 5> buff_2 = mk::stdlib::move(buff);

			MK_STDLIB_ASSERT(buff.empty() == true);
			MK_STDLIB_ASSERT(buff.full() == false);
			MK_STDLIB_ASSERT(buff.size() == 0);
			MK_STDLIB_ASSERT(buff.capacity() == 8);
			MK_STDLIB_ASSERT(buff.free() == 8);
			MK_STDLIB_ASSERT(buff.first_half().size() == 0);
			MK_STDLIB_ASSERT(buff.second_half().size() == 0);

			MK_STDLIB_ASSERT(buff_2.empty() == false);
			MK_STDLIB_ASSERT(buff_2.full() == false);
			MK_STDLIB_ASSERT(buff_2.size() == 2);
			MK_STDLIB_ASSERT(buff_2.capacity() == 8);
			MK_STDLIB_ASSERT(buff_2.free() == 6);
			MK_STDLIB_ASSERT(buff_2.first_half().size() == 2);
			MK_STDLIB_ASSERT(buff_2.first_half()[0] == t{});
			MK_STDLIB_ASSERT(buff_2.first_half()[1] == t{});
			MK_STDLIB_ASSERT(buff_2.second_half().size() == 0);
			MK_STDLIB_ASSERT(buff_2[0] == t{});
			MK_STDLIB_ASSERT(buff_2[1] == t{});
		}
	}
	{
		for(int i = 0; i != 100; ++i)
		{
			mk::stdlib::ring_buffer_t<t, 5> buff;
			buff.push_back(t{});
			buff.push_back(t{});
			for(int j = 0; j != i; ++j)
			{
				buff.pop_front();
				buff.push_back(t{});
			}

			mk::stdlib::ring_buffer_t<t, 5> buff_2;
			buff_2 = mk::stdlib::move(buff);

			MK_STDLIB_ASSERT(buff.empty() == true);
			MK_STDLIB_ASSERT(buff.full() == false);
			MK_STDLIB_ASSERT(buff.size() == 0);
			MK_STDLIB_ASSERT(buff.capacity() == 8);
			MK_STDLIB_ASSERT(buff.free() == 8);
			MK_STDLIB_ASSERT(buff.first_half().size() == 0);
			MK_STDLIB_ASSERT(buff.second_half().size() == 0);

			MK_STDLIB_ASSERT(buff_2.empty() == false);
			MK_STDLIB_ASSERT(buff_2.full() == false);
			MK_STDLIB_ASSERT(buff_2.size() == 2);
			MK_STDLIB_ASSERT(buff_2.capacity() == 8);
			MK_STDLIB_ASSERT(buff_2.free() == 6);
			MK_STDLIB_ASSERT(buff_2.first_half().size() == 2);
			MK_STDLIB_ASSERT(buff_2.first_half()[0] == t{});
			MK_STDLIB_ASSERT(buff_2.first_half()[1] == t{});
			MK_STDLIB_ASSERT(buff_2.second_half().size() == 0);
			MK_STDLIB_ASSERT(buff_2[0] == t{});
			MK_STDLIB_ASSERT(buff_2[1] == t{});
		}
	}
}

#include "copy.hpp"


template<typename t1, typename t2, typename t3>
void mk::stdlib::copy(t1 const& src_begin, t2 const& src_end, t3 const& dst) noexcept
{
	t1 it_src = src_begin;
	t3 it_dst = dst;
	while(it_src != dst)
	{
		*it_dst = *it_src;
		++it_src;
		++it_dst;
	}
}

template<typename t1, typename t2, typename t3>
void mk::stdlib::copy_n(t1 const& src, t2 const& count, t3 const& dst) noexcept
{
	t1 it_src = src_begin;
	t2 cnt = count;
	t3 it_dst = dst;
	while(cnt)
	{
		*it_dst = *it_src;
		++it_src;
		--cnt;
		++it_dst;
	}
}

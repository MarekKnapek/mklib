#include "fill.hpp"


template<typename t1, typename t2, typename t3>
void mk::stdlib::fill(t1 const& dst_begin, t2 const& dst_end, t3 const& val) noexcept
{
	t1 it_dst = dst_begin;
	while(it_dst != dst_end)
	{
		*it_dst = val;
		++it_dst;
	}
}

template<typename t1, typename t2, typename t3>
t1 mk::stdlib::fill_n(t1 const& dst, t2 const& count, t3 const& val) noexcept
{
	t1 it_dst = dst;
	t2 cnt = count;
	while(cnt)
	{
		*it_dst = val;
		--cnt;
		++it_dst;
	}
	return it_dst;
}

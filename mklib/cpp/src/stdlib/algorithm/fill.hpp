#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t1, typename t2, typename t3> void fill(t1 const& dst_begin, t2 const& dst_end, t3 const& val) noexcept;
		template<typename t1, typename t2, typename t3> t1 fill_n(t1 const& dst, t2 const& count, t3 const& val) noexcept;


	}
}


#include "fill.inl"

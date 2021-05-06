#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t1, typename t2, typename t3> void copy(t1 const& src_begin, t2 const& src_end, t3 const& dst) noexcept;
		template<typename t1, typename t2, typename t3> void copy_n(t1 const& src, t2 const& count, t3 const& dst) noexcept;


	}
}


#include "copy.inl"

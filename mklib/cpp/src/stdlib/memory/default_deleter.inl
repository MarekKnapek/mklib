#include "default_deleter.h"

#include "../cstdlib.hpp" // mk::stdlib::free
#include "../ints.hpp" // mk::stdlib::uintptr_t
#include "../memory.hpp" // mk::stdlib::destroy_n
#include "../size.hpp" // mk::stdlib::size_t
#include "../type_traits/is_trivial.hpp" // mk::stdlib::is_trivial_t


template<typename t>
void mk::stdlib::default_deleter_t<t>::operator()(t const* const& ptr) const noexcept
{
	if constexpr(!mk::stdlib::is_trivial_t<t>::s_value)
	{
		mk::stdlib::destroy_at(ptr);
	}
	mk::stdlib::free(ptr);
}

template<typename t>
void mk::stdlib::default_deleter_t<t[]>::operator()(t const* const& ptr) const noexcept
{
	if constexpr(mk::stdlib::is_trivial_t<t>::s_value)
	{
		mk::stdlib::free(ptr);
	}
	else
	{
		void* const mem = reinterpret_cast<void*>(reinterpret_cast<mk::stdlib::uintptr_t>(ptr) - sizeof(mk::stdlib::size_t));
		mk::stdlib::size_t const count = *reinterpret_cast<mk::stdlib::size_t*>(mem);
		mk::stdlib::destroy_n(ptr, count);
		mk::stdlib::free(mem);
	}
}

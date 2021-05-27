#include "default_deleter.h"

#include "../assert.hpp" // MK_STDLIB_ASSERT
#include "../cstdlib.hpp" // free
#include "../ints.hpp" // uintptr_t
#include "../memory.hpp" // destroy_at, destroy_n
#include "../size.hpp" // size_t
#include "../type_traits/is_trivial.hpp" // is_trivial_t


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
	if constexpr(!mk::stdlib::is_trivial_t<t>::s_value)
	{
		mk::stdlib::uintptr_t const count_pos = reinterpret_cast<mk::stdlib::uintptr_t>(ptr) - sizeof(mk::stdlib::size_t);
		MK_STDLIB_ASSERT((count_pos % alignof(mk::stdlib::size_t)) == 0);
		mk::stdlib::size_t const count = *reinterpret_cast<mk::stdlib::size_t const*>(count_pos);
		mk::stdlib::destroy_n(ptr, count);
	}
	mk::stdlib::free(ptr);
}

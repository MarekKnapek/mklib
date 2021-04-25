#include "new.hpp"


[[nodiscard]] void* operator new(mk::stdlib::size_t const size, void* const& place, mk::stdlib::new_t const& tag) noexcept
{
	(void)size;
	(void)tag;
	return place;
}

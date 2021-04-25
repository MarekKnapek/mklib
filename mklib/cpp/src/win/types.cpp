#include "types.hpp"


mk::win::handle_t::operator bool() const noexcept
{
	return m_value != nullptr;
}

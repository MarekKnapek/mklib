#include "assert.hpp"


void mk::stdlib::assert_failed() noexcept
{
	__debugbreak();
}

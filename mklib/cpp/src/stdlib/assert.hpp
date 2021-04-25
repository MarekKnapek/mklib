#pragma once


#define MK_STDLIB_ASSERT(X) do{if(X){}else{assert_failed();}}while(false)
#define MK_STDLIB_UNREACHABLE() do{__assume(false);}while(false)


namespace mk
{
	namespace stdlib
	{

		void assert_failed() noexcept;

	}
}

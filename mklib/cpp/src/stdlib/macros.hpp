#pragma once


#define MK_STDLIB_UNREACHABLE() do{__assume(false);}while(false)

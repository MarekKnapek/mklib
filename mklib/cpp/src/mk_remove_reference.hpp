#pragma once


namespace mk
{

	template<typename t> struct remove_reference_t { typedef t type; };
	template<typename t> struct remove_reference_t<t&> { typedef t type; };
	template<typename t> struct remove_reference_t<t&&> { typedef t type; };

}

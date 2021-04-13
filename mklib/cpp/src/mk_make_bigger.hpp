#pragma once


namespace mk
{

	template<typename> struct make_bigger_t{};
	template<> struct make_bigger_t<unsigned __int8> { typedef unsigned __int16 type; };
	template<> struct make_bigger_t<unsigned __int16> { typedef unsigned __int32 type; };
	template<> struct make_bigger_t<unsigned __int32> { typedef unsigned __int64 type; };
	template<> struct make_bigger_t<signed __int8> { typedef signed __int16 type; };
	template<> struct make_bigger_t<signed __int16> { typedef signed __int32 type; };
	template<> struct make_bigger_t<signed __int32> { typedef signed __int64 type; };

}

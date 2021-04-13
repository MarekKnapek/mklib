#pragma once


namespace mk
{

	template<typename> struct make_signed_t{};
	template<> struct make_signed_t<unsigned __int8> { typedef signed __int8 type; };
	template<> struct make_signed_t<unsigned __int16> { typedef signed __int16 type; };
	template<> struct make_signed_t<unsigned __int32> { typedef signed __int32 type; };
	template<> struct make_signed_t<unsigned __int64> { typedef signed __int64 type; };
	template<> struct make_signed_t<signed __int8> { typedef signed __int8 type; };
	template<> struct make_signed_t<signed __int16> { typedef signed __int16 type; };
	template<> struct make_signed_t<signed __int32> { typedef signed __int32 type; };
	template<> struct make_signed_t<signed __int64> { typedef signed __int64 type; };

}

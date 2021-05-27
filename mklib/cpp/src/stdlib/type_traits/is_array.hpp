#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t>
		struct is_array_t
		{
			static constexpr bool const s_value = false;
		};

		template<typename t>
		struct is_array_t<t[]>
		{
			static constexpr bool const s_value = true;
		};

		template<typename t, unsigned n>
		struct is_array_t<t[n]>
		{
			static constexpr bool const s_value = true;
		};


	}
}

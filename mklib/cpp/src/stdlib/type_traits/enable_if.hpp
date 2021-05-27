#pragma once


namespace mk
{
	namespace stdlib
	{


		template<bool b, typename t = void>
		struct enable_if_t
		{
		};

		template<typename t>
		struct enable_if_t<true, t>
		{
			typedef t type_t;
		};


	}
}

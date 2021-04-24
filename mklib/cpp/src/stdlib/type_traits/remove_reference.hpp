#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t>
		struct remove_reference_t
		{
			typedef t type_t;
		};

		template<typename t>
		struct remove_reference_t<t&>
		{
			typedef t type_t;
		};

		template<typename t>
		struct remove_reference_t<t&&>
		{
			typedef t type_t;
		};


	}
}

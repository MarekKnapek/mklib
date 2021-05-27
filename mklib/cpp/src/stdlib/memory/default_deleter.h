#pragma once


namespace mk
{
	namespace stdlib
	{


		template<typename t>
		struct default_deleter_t
		{
			void operator()(t const* const& ptr) const noexcept;
		};

		template<typename t>
		struct default_deleter_t<t[]>
		{
			void operator()(t const* const& ptr) const noexcept;
		};


	}
}


#include "default_deleter.inl"

#pragma once


namespace mk
{
	namespace stdlib
	{


		template<unsigned s, unsigned a = alignof(void*)>
		struct aligned_storage_t
		{
			struct type_t
			{
				alignas(a) unsigned char m_data[s];
			};
		};

		template<typename t>
		using aligned_storage_helper_t = typename mk::stdlib::aligned_storage_t<sizeof(t), alignof(t)>::type_t;
	
	
	}
}

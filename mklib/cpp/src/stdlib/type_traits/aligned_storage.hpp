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
	
	
	}
}

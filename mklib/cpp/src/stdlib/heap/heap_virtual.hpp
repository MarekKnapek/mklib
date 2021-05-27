#pragma once


#include "../size.hpp"
#include "../type_traits/aligned_storage.hpp"


namespace mk
{
	namespace stdlib
	{


		class heap_virtual_t
		{
		public:
			heap_virtual_t() noexcept;
			template<typename t> [[nodiscard]] static mk::stdlib::heap_virtual_t make() noexcept;
			heap_virtual_t(mk::stdlib::heap_virtual_t const&) = delete;
			heap_virtual_t(mk::stdlib::heap_virtual_t&& other) noexcept;
			mk::stdlib::heap_virtual_t& operator=(mk::stdlib::heap_virtual_t const&) = delete;
			mk::stdlib::heap_virtual_t& operator=(mk::stdlib::heap_virtual_t&& other) noexcept;
			~heap_virtual_t() noexcept;
			explicit operator bool() const noexcept;
			void swap(mk::stdlib::heap_virtual_t& other) noexcept;
		private:
			void destroy() noexcept;
		public:
			[[nodiscard]] void* alloc(mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] mk::stdlib::size_t size(void const* const& mem) const noexcept;
			[[nodiscard]] void* realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] void* realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			void free(void const* const& mem) noexcept;
		private:
			int m_type;
			mk::stdlib::aligned_storage_t<2 * sizeof(void*)>::type_t m_storage;
		};

		inline void swap(mk::stdlib::heap_virtual_t& a, mk::stdlib::heap_virtual_t& b) noexcept { a.swap(b); }


	}
}

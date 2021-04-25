#pragma once


#include "../../win/types.hpp"
#include "../size.hpp"


namespace mk
{
	namespace stdlib
	{


		class heap_process_t
		{
		public:
			heap_process_t() noexcept;
			heap_process_t(mk::stdlib::heap_process_t const&) = delete;
			heap_process_t(mk::stdlib::heap_process_t&& other) noexcept;
			mk::stdlib::heap_process_t& operator=(mk::stdlib::heap_process_t const&) = delete;
			mk::stdlib::heap_process_t& operator=(mk::stdlib::heap_process_t&& other) noexcept;
			~heap_process_t() noexcept;
			explicit operator bool() const noexcept;
			void swap(mk::stdlib::heap_process_t& other) noexcept;
		public:
			[[nodiscard]] void* alloc(mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] mk::stdlib::size_t size(void const* const& mem) const noexcept;
			[[nodiscard]] void* realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] void* realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			void free(void* const& mem) noexcept;
		private:
			mk::win::handle_t m_heap;
		};

		inline void swap(mk::stdlib::heap_process_t& a, mk::stdlib::heap_process_t& b) noexcept { a.swap(b); }


	}
}

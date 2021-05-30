#pragma once


#include "../../win/types.hpp"
#include "../size.hpp"


namespace mk
{
	namespace stdlib
	{


		class heap_multi_threaded_t
		{
		public:
			heap_multi_threaded_t() noexcept;
			heap_multi_threaded_t(mk::stdlib::heap_multi_threaded_t const&) = delete;
			heap_multi_threaded_t(mk::stdlib::heap_multi_threaded_t&& other) noexcept;
			mk::stdlib::heap_multi_threaded_t& operator=(mk::stdlib::heap_multi_threaded_t const&) = delete;
			mk::stdlib::heap_multi_threaded_t& operator=(mk::stdlib::heap_multi_threaded_t&& other) noexcept;
			~heap_multi_threaded_t() noexcept;
			void swap(mk::stdlib::heap_multi_threaded_t& other) noexcept;
			[[nodiscard]] explicit operator bool() const noexcept;
		public:
			[[nodiscard]] static mk::stdlib::heap_multi_threaded_t make() noexcept;
			[[nodiscard]] mk::win::handle_t const& get() const noexcept;
		public:
			[[nodiscard]] void* alloc(mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] mk::stdlib::size_t size(void const* const& mem) const noexcept;
			[[nodiscard]] void* realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] void* realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			void free(void const* const& mem) noexcept;
		private:
			explicit heap_multi_threaded_t(mk::win::handle_t const& heap) noexcept;
		private:
			mk::win::handle_t m_heap;
		};

		inline void swap(mk::stdlib::heap_multi_threaded_t& a, mk::stdlib::heap_multi_threaded_t& b) noexcept { a.swap(b); }


	}
}

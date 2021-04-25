#pragma once


#include "../../win/types.hpp"
#include "../size.hpp"


namespace mk { namespace stdlib { class heap_multi_threaded_t; } }
namespace mk { namespace stdlib { class heap_process_t; } }
namespace mk { namespace stdlib { class heap_single_threaded_t; } }
namespace mk { namespace stdlib { class heap_type_erased_t; } }
namespace mk { namespace stdlib { class heap_virtual_t; } }


namespace mk
{
	namespace stdlib
	{


		class heap_type_erased_t
		{
		public:
			heap_type_erased_t() noexcept;
			explicit heap_type_erased_t(mk::stdlib::heap_multi_threaded_t& heap) noexcept;
			explicit heap_type_erased_t(mk::stdlib::heap_process_t& heap) noexcept;
			explicit heap_type_erased_t(mk::stdlib::heap_single_threaded_t& heap) noexcept;
			explicit heap_type_erased_t(mk::stdlib::heap_type_erased_t& heap) noexcept;
			explicit heap_type_erased_t(mk::stdlib::heap_virtual_t& heap) noexcept;
			heap_type_erased_t(mk::stdlib::heap_type_erased_t const&) = delete;
			heap_type_erased_t(mk::stdlib::heap_type_erased_t&& other) noexcept;
			mk::stdlib::heap_type_erased_t& operator=(mk::stdlib::heap_type_erased_t const&) = delete;
			mk::stdlib::heap_type_erased_t& operator=(mk::stdlib::heap_type_erased_t&& other) noexcept;
			~heap_type_erased_t() noexcept;
			explicit operator bool() const noexcept;
			void swap(mk::stdlib::heap_type_erased_t& other) noexcept;
		public:
			[[nodiscard]] void* alloc(mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] mk::stdlib::size_t size(void const* const& mem) const noexcept;
			[[nodiscard]] void* realloc(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			[[nodiscard]] void* realloc_inplace(void* const& mem, mk::stdlib::size_t const& bytes) noexcept;
			void free(void* const& mem) noexcept;
		private:
			int m_type;
			void* m_heap;
		};

		inline void swap(mk::stdlib::heap_type_erased_t& a, mk::stdlib::heap_type_erased_t& b) noexcept { a.swap(b); }


	}
}

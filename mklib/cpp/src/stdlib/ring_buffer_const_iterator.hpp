#pragma once


#include "size.hpp" // mk::stdlib::size_t
#include "ring_buffer.hpp" // mk::stdlib::ring_buffer_t


namespace mk { namespace stdlib { template<typename, mk::stdlib::size_t> class ring_buffer_iterator_t; } }


namespace mk
{
	namespace stdlib
	{


		template<typename t, mk::stdlib::size_t n>
		class ring_buffer_const_iterator_t
		{
		public:
			ring_buffer_const_iterator_t() noexcept;
			ring_buffer_const_iterator_t(mk::stdlib::ring_buffer_t<t, n> const* const& ring_buffer, mk::stdlib::size_t const& idx) noexcept;
			explicit(false) ring_buffer_const_iterator_t(mk::stdlib::ring_buffer_iterator_t<t, n> const& other) noexcept;
			ring_buffer_const_iterator_t(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) noexcept;
			ring_buffer_const_iterator_t(mk::stdlib::ring_buffer_const_iterator_t<t, n>&& other) noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator=(mk::stdlib::ring_buffer_const_iterator_t<t, n>&& other) noexcept;
			~ring_buffer_const_iterator_t() noexcept;
			void swap(mk::stdlib::ring_buffer_const_iterator_t<t, n>& other) noexcept;
			[[nodiscard]] mk::stdlib::ring_buffer_t<t, n> const* const& get_ring_buffer() const noexcept;
			[[nodiscard]] mk::stdlib::size_t const& get_idx() const noexcept;
		public:
			[[nodiscard]] bool operator==(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] bool operator!=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] bool operator<(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] bool operator>(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] bool operator<=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] bool operator>=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> operator+(mk::stdlib::ptrdiff_t const& amount) const noexcept;
			[[nodiscard]] mk::stdlib::ring_buffer_const_iterator_t<t, n> operator-(mk::stdlib::ptrdiff_t const& amount) const noexcept;
			[[nodiscard]] mk::stdlib::ptrdiff_t operator-(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) const noexcept;
			[[nodiscard]] t const& operator*() const noexcept;
			[[nodiscard]] t const& operator[](mk::stdlib::size_t const& idx) const noexcept;
		public:
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator++() noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator--() noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n> operator++(int) noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n> operator--(int) noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator+=(mk::stdlib::ptrdiff_t const& amount) noexcept;
			mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator-=(mk::stdlib::ptrdiff_t const& amount) noexcept;
		private:
			static constexpr inline mk::stdlib::size_t const s_minus_one = static_cast<mk::stdlib::size_t>(0) - 1;
		private:
			mk::stdlib::ring_buffer_t<t, n> const* m_ring_buffer;
			mk::stdlib::size_t m_idx;
		};

		template<typename t, mk::stdlib::size_t n> inline void swap(mk::stdlib::ring_buffer_const_iterator_t<t, n>& a, mk::stdlib::ring_buffer_const_iterator_t<t, n>& b) noexcept { a.swap(b); }

		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator==(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator==(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator!=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator!=(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator<(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator<(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator>(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator>(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator<=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator<=(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline bool operator>=(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& a, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& b) noexcept { return a.operator>=(b); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline mk::stdlib::ring_buffer_const_iterator_t<t, n> operator+(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& self, mk::stdlib::ptrdiff_t const& amount) noexcept { return self.operator+(amount); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline mk::stdlib::ring_buffer_const_iterator_t<t, n> operator+(mk::stdlib::ptrdiff_t const& amount, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& self) noexcept { return self.operator+(amount); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline mk::stdlib::ring_buffer_const_iterator_t<t, n> operator-(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& self, mk::stdlib::ptrdiff_t const& amount) noexcept { return self.operator-(amount); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline mk::stdlib::ptrdiff_t operator-(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& self, mk::stdlib::ring_buffer_const_iterator_t<t, n> const& other) noexcept { return self.operator-(other); }
		template<typename t, mk::stdlib::size_t n> [[nodiscard]] inline t& operator*(mk::stdlib::ring_buffer_const_iterator_t<t, n> const& self) noexcept { return self.operator*(); }

		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator++(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self) noexcept { return self.operator++(); }
		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator--(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self) noexcept { return self.operator--(); }
		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n> operator++(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self, int const dummy) noexcept { return self.operator++(dummy); }
		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n> operator--(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self, int const dummy) noexcept { return self.operator--(dummy); }
		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator+=(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self, mk::stdlib::ptrdiff_t const& amount) noexcept { return self.operator+=(amount); }
		template<typename t, mk::stdlib::size_t n> inline mk::stdlib::ring_buffer_const_iterator_t<t, n>& operator-=(mk::stdlib::ring_buffer_const_iterator_t<t, n>& self, mk::stdlib::ptrdiff_t const& amount) noexcept { return self.operator-=(amount); }


	}
}


#include "ring_buffer_const_iterator.inl"

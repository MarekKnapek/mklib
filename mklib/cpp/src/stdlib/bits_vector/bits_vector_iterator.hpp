#pragma once


#include "bits_vector_proxy_reference.hpp"

#include "../size.hpp"


namespace mk { namespace stdlib { template<typename t, unsigned n, typename chunk_t> class bits_vector_const_iterator_t; } }


namespace mk
{
	namespace stdlib
	{


		template<typename t, unsigned n, typename chunk_t = mk::stdlib::size_t>
		class bits_vector_iterator_t
		{
		public:
			bits_vector_iterator_t() noexcept;
			bits_vector_iterator_t(chunk_t* const& chunk, mk::stdlib::size_t const& idx) noexcept;
			bits_vector_iterator_t(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) noexcept;
			bits_vector_iterator_t(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>&& other) noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>&& other) noexcept;
			~bits_vector_iterator_t() noexcept;
			void swap(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& other) noexcept;
			[[nodiscard]] chunk_t* const& get_chunk() const noexcept;
			[[nodiscard]] mk::stdlib::size_t const& get_idx() const noexcept;
		public:
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> operator*() const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> operator[](mk::stdlib::ptrdiff_t const& idx) const noexcept;
			[[nodiscard]] bool operator==(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator==(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator!=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator!=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator<(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator<(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator>(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator>(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator<=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator<=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator>=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] bool operator>=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator+(mk::stdlib::ptrdiff_t const& steps) const noexcept;
			[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator-(mk::stdlib::ptrdiff_t const& steps) const noexcept;
			[[nodiscard]] mk::stdlib::ptrdiff_t operator-(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept;
			[[nodiscard]] mk::stdlib::ptrdiff_t operator-(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept;
		public:
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator++() noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator--() noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator++(int) noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator--(int) noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator+=(mk::stdlib::ptrdiff_t const& steps) noexcept;
			mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator-=(mk::stdlib::ptrdiff_t const& steps) noexcept;
		private:
			static constexpr unsigned const s_elements_per_chunk = sizeof(chunk_t) * mk::stdlib::s_char_bit / n;
			chunk_t* m_chunk;
			mk::stdlib::size_t m_idx;
		};

		template<typename t, unsigned n, typename chunk_t> inline void swap(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& b) noexcept { a.swap(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> operator*(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& self) noexcept { return self.operator*(); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator==(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator==(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator==(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator==(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator!=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator!=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator!=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator!=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator<(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator<(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator<(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator<(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator>(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator>(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator>(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator>(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator<=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator<=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator<=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator<=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator>=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator>=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline bool operator>=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator>=(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator+(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& self, mk::stdlib::ptrdiff_t const& steps) noexcept { return self.operator+(steps); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator-(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& self, mk::stdlib::ptrdiff_t const& steps) noexcept { return self.operator-(steps); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator+(mk::stdlib::ptrdiff_t const& steps, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& self) noexcept { return self.operator+(steps); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator-(mk::stdlib::ptrdiff_t const& steps, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& self) noexcept { return self.operator-(steps); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::ptrdiff_t operator-(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator-(b); }
		template<typename t, unsigned n, typename chunk_t> [[nodiscard]] inline mk::stdlib::ptrdiff_t operator-(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& a, mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& b) noexcept { return a.operator-(b); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator++(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self) noexcept { return self.operator++(); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator--(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self) noexcept { return self.operator--(); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator++(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self, int const i) noexcept { return self.operator++(i); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> operator--(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self, int const i) noexcept { return self.operator--(i); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator+=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self, mk::stdlib::ptrdiff_t const& steps) noexcept { return self.operator+=(steps); }
		template<typename t, unsigned n, typename chunk_t> inline mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& operator-=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& self, mk::stdlib::ptrdiff_t const& steps) noexcept { return self.operator-=(steps); }


	}
}


#include "bits_vector_iterator.inl"

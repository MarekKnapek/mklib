#include "bits_vector_iterator.hpp"

#include "bits_vector_const_iterator.hpp"

#include "../assert.hpp"
#include "../climits.hpp"
#include "../utility/move.hpp"
#include "../utility/swap.hpp"


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::bits_vector_iterator_t() noexcept :
	m_chunk(),
	m_idx()
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::bits_vector_iterator_t(chunk_t* const& chunk, mk::stdlib::size_t const& idx) noexcept :
	m_chunk(chunk),
	m_idx(idx)
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::bits_vector_iterator_t(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) noexcept :
	m_chunk(other.m_chunk),
	m_idx(other.m_idx)
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::bits_vector_iterator_t(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>&& other) noexcept :
	m_chunk(mk::stdlib::move(other.m_chunk)),
	m_idx(mk::stdlib::move(other.m_idx))
{
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) noexcept
{
	m_chunk = other.m_chunk;
	m_idx = other.m_idx;
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>&& other) noexcept
{
	m_chunk = mk::stdlib::move(other.m_chunk);
	m_idx = mk::stdlib::move(other.m_idx);
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::~bits_vector_iterator_t() noexcept
{
}

template<typename t, unsigned n, typename chunk_t>
void mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::swap(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_chunk, other.m_chunk);
	swap(m_idx, other.m_idx);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] chunk_t* const& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::get_chunk() const noexcept
{
	return m_chunk;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::size_t const& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::get_idx() const noexcept
{
	return m_idx;
}


template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator*() const noexcept
{
	return mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t>{m_chunk, m_idx};
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_proxy_reference_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator[](mk::stdlib::ptrdiff_t const& idx) const noexcept
{
	return *(*this + idx);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator==(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	bool const eq = m_chunk == other.m_chunk && m_idx == other.m_idx;
	return eq;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator==(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	bool const eq = m_chunk == other.get_chunk() && m_idx == other.get_idx();
	return eq;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator!=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !operator==(other);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator!=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !operator==(other);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator<(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	if(m_chunk < other.m_chunk)
	{
		return true;
	}
	else if(other.m_chunk < m_chunk)
	{
		return false;
	}
	else
	{
		return m_idx < other.m_idx;
	}
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator<(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	if(m_chunk < other.get_chunk())
	{
		return true;
	}
	else if(other.get_chunk() < m_chunk)
	{
		return false;
	}
	else
	{
		return m_idx < other.get_idx();
	}
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator>(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return other < *this;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator>(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return other < *this;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator<=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !(other < *this);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator<=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !(other < *this);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator>=(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !(*this < other);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] bool mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator>=(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	return !(*this < other);
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator+(mk::stdlib::ptrdiff_t const& steps) const noexcept
{
	mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> copy = *this;
	return copy += steps;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator-(mk::stdlib::ptrdiff_t const& steps) const noexcept
{
	mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> copy = *this;
	return copy -= steps;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::ptrdiff_t mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator-(mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	mk::stdlib::ptrdiff_t const steps = (m_chunk - other.m_chunk) * s_elements_per_chunk + (m_idx - other.m_idx);
	return steps;
}

template<typename t, unsigned n, typename chunk_t>
[[nodiscard]] mk::stdlib::ptrdiff_t mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator-(mk::stdlib::bits_vector_const_iterator_t<t, n, chunk_t> const& other) const noexcept
{
	mk::stdlib::ptrdiff_t const steps = (m_chunk - other.get_chunk()) * s_elements_per_chunk + (m_idx - other.get_idx());
	return steps;
}


template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator++() noexcept
{
	bool const end_of_chunk = m_idx == s_elements_per_chunk - 1;
	if(!end_of_chunk)
	{
		++m_idx;
	}
	else
	{
		++m_chunk;
		m_idx = 0;
	}
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator--() noexcept
{
	bool const start_of_chunk = m_idx == 0;
	if(!start_of_chunk)
	{
		--m_idx;
	}
	else
	{
		--m_chunk;
		m_idx = s_elements_per_chunk - 1;
	}
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator++(int) noexcept
{
	mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> copy = *this;
	operator++();
	return copy;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator--(int) noexcept
{
	mk::stdlib::bits_vector_iterator_t<t, n, chunk_t> copy = *this;
	operator--();
	return copy;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator+=(mk::stdlib::ptrdiff_t const& steps) noexcept
{
	bool const is_negative = steps < 0;
	if(!is_negative)
	{
		m_chunk += steps / s_elements_per_chunk;
		m_idx += steps % s_elements_per_chunk;
		if(m_idx >= s_elements_per_chunk)
		{
			++m_chunk;
			m_idx -= s_elements_per_chunk;
		}
	}
	else
	{
		mk::stdlib::ptrdiff_t const positive = -steps;
		m_chunk -= positive / s_elements_per_chunk;
		m_idx -= positive % s_elements_per_chunk;
		if(m_idx <= static_cast<mk::stdlib::size_t>(-1))
		{
			--m_chunk;
			m_idx += s_elements_per_chunk;
		}
	}
	return *this;
}

template<typename t, unsigned n, typename chunk_t>
mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>& mk::stdlib::bits_vector_iterator_t<t, n, chunk_t>::operator-=(mk::stdlib::ptrdiff_t const& steps) noexcept
{
	return operator+=(-steps);
}

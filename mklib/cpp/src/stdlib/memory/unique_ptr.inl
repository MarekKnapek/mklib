#include "unique_ptr.hpp"

#include "../assert.hpp"
#include "../utility/swap.hpp"


template<typename t, typename d>
mk::stdlib::unique_ptr_t<t, d>::unique_ptr_t() noexcept :
	m_ptr()
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t, d>::unique_ptr_t(t* const& ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t, d>::unique_ptr_t(mk::stdlib::unique_ptr_t<t, d>&& other) noexcept :
	mk::stdlib::unique_ptr_t<t, d>()
{
	swap(other);
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t, d>& mk::stdlib::unique_ptr_t<t, d>::operator=(mk::stdlib::unique_ptr_t<t, d>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t, d>::~unique_ptr_t() noexcept
{
	if(m_ptr == nullptr)
	{
		return;
	}
	d{}(m_ptr);
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t, d>::swap(mk::stdlib::unique_ptr_t<t, d>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_ptr, other.m_ptr);
}


template<typename t, typename d>
[[nodiscard]] t* const& mk::stdlib::unique_ptr_t<t, d>::get() const noexcept
{
	return m_ptr;
}

template<typename t, typename d>
[[nodiscard]] mk::stdlib::unique_ptr_t<t, d>::operator bool() const noexcept
{
	return m_ptr != nullptr;
}

template<typename t, typename d>
[[nodiscard]] t* mk::stdlib::unique_ptr_t<t, d>::operator->() const noexcept
{
	MK_STDLIB_ASSERT(m_ptr != nullptr);
	return m_ptr;
}

template<typename t, typename d>
[[nodiscard]] t& mk::stdlib::unique_ptr_t<t, d>::operator*() const noexcept
{
	MK_STDLIB_ASSERT(m_ptr != nullptr);
	return *m_ptr;
}


template<typename t, typename d>
[[nodiscard]] t* mk::stdlib::unique_ptr_t<t, d>::release() noexcept
{
	t* const ptr = m_ptr;
	m_ptr = nullptr;
	return ptr;
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t, d>::reset(t* const& ptr) noexcept
{
	MK_STDLIB_ASSERT((m_ptr == nullptr) || (m_ptr != ptr));
	mk::stdlib::unique_ptr_t<t[], d> new_up{ptr};
	swap(new_up);
}




template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t() noexcept :
	m_ptr()
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t(t* const& ptr) noexcept :
	m_ptr(ptr)
{
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::unique_ptr_t(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept :
	mk::stdlib::unique_ptr_t<t[], d>()
{
	swap(other);
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>& mk::stdlib::unique_ptr_t<t[], d>::operator=(mk::stdlib::unique_ptr_t<t[], d>&& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	swap(other);
	return *this;
}

template<typename t, typename d>
mk::stdlib::unique_ptr_t<t[], d>::~unique_ptr_t() noexcept
{
	if(m_ptr == nullptr)
	{
		return;
	}
	d{}(m_ptr);
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t[], d>::swap(mk::stdlib::unique_ptr_t<t[], d>& other) noexcept
{
	MK_STDLIB_ASSERT(this != &other);
	using mk::stdlib::swap;
	swap(m_ptr, other.m_ptr);
}


template<typename t, typename d>
[[nodiscard]] t* const& mk::stdlib::unique_ptr_t<t[], d>::get() const noexcept
{
	return m_ptr;
}

template<typename t, typename d>
[[nodiscard]] mk::stdlib::unique_ptr_t<t[], d>::operator bool() const noexcept
{
	return m_ptr != nullptr;
}

template<typename t, typename d>
[[nodiscard]] t& mk::stdlib::unique_ptr_t<t[], d>::operator[](mk::stdlib::size_t const& idx) const noexcept
{
	MK_STDLIB_ASSERT(m_ptr != nullptr);
	return m_ptr[idx];
}


template<typename t, typename d>
[[nodiscard]] t* mk::stdlib::unique_ptr_t<t[], d>::release() noexcept
{
	t* const ptr = m_ptr;
	m_ptr = nullptr;
	return ptr;
}

template<typename t, typename d>
void mk::stdlib::unique_ptr_t<t[], d>::reset(t* const& ptr) noexcept
{
	MK_STDLIB_ASSERT((m_ptr == nullptr) || (m_ptr != ptr));
	mk::stdlib::unique_ptr_t<t[], d> new_up{ptr};
	swap(new_up);
}

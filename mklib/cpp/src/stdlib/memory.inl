#include "memory.h"

#include "new.hpp"
#include "type_traits/remove_reference.hpp"
#include "utility/forward.hpp"
#include "utility/move.hpp"


template<typename t, typename... ts>
constexpr t* mk::stdlib::construct_at(t* const& ptr, ts&&... params) noexcept
{
	void* const newd = new(static_cast<void*>(ptr), mk::stdlib::new_t{})t(mk::stdlib::forward<ts>(params)...);
	t* const ret = static_cast<t*>(newd);
	return ret;
}

template<typename t>
constexpr void mk::stdlib::destroy(t& val) noexcept
{
	val.~t();
}

template<typename t>
constexpr void mk::stdlib::destroy_at(t const& it) noexcept
{
	mk::stdlib::destroy(*it);
}


template<typename t, typename u>
void mk::stdlib::uninitialized_default_construct(t const& begin, u const& end) noexcept
{
	t it = begin;
	while(it != end)
	{
		mk::stdlib::construct_at(it);
		++it;
	}
}

template<typename t, typename u, typename v>
v mk::stdlib::uninitialized_copy(t const& input_begin, u const& input_end, v const& output_begin) noexcept
{
	t input_it = input_begin;
	v output_it = output_begin;
	while(input_it != input_end)
	{
		mk::stdlib::construct_at(output_it, *input_it);
		++input_it;
		++output_it;
	}
	return output_it;
}

template<typename t, typename u, typename v>
v mk::stdlib::uninitialized_move(t const& input_begin, u const& input_end, v const& output_begin) noexcept
{
	t input_it = input_begin;
	v output_it = output_begin;
	while(input_it != input_end)
	{
		mk::stdlib::construct_at(output_it, mk::stdlib::move(*input_it));
		++input_it;
		++output_it;
	}
	return output_it;
}

template<typename t, typename u, typename v>
v mk::stdlib::uninitialized_move_destroy(t const& input_begin, u const& input_end, v const& output_begin) noexcept
{
	t input_it = input_begin;
	v output_it = output_begin;
	while(input_it != input_end)
	{
		mk::stdlib::construct_at(output_it, mk::stdlib::move(*input_it));
		mk::stdlib::destroy_at(input_it);
		++input_it;
		++output_it;
	}
	return output_it;
}

template<typename t, typename u>
constexpr void mk::stdlib::destroy(t const& begin, u const& end) noexcept
{
	t it = begin;
	while(it != end)
	{
		mk::stdlib::destroy_at(it);
		++it;
	}
}


template<typename t, typename u>
t mk::stdlib::uninitialized_default_construct_n(t const& begin, u const& count) noexcept
{
	t it = begin;
	u n = count;
	while(n != 0)
	{
		mk::stdlib::construct_at(it);
		++it;
		--n;
	}
	return it;
}

template<typename t, typename u, typename v>
v mk::stdlib::uninitialized_copy_n(t const& input_begin, u const& size, v const& output_begin) noexcept
{
	t input_it = input_begin;
	u n = size;
	v ouput_it = output_begin;
	while(n != 0)
	{
		mk::stdlib::construct_at(output_begin, *input_it);
		++input_it;
		--n;
		++ouput_it;
	}
}

template<typename t, typename u, typename v>
v mk::stdlib::uninitialized_move_destroy_n(t const& input_begin, u const& input_size, v const& output_begin) noexcept
{
	t input_it = input_begin;
	u n = input_size;
	v output_it = output_begin;
	while(n != 0)
	{
		mk::stdlib::construct_at(output_it, mk::stdlib::move(*input_it));
		mk::stdlib::destroy_at(input_it);
		++input_it;
		--n;
		++output_it;
	}
	return output_it;
}

template<typename t, typename u>
constexpr t mk::stdlib::destroy_n(t const& begin, u const& size) noexcept
{
	t it = begin;
	u n = size;
	while(n != 0)
	{
		mk::stdlib::destroy(*it);
		++it;
		--n;
	}
	return it;
}

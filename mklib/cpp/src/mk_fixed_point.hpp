#pragma once


namespace mk
{


	template<typename t, unsigned n>
	class fixed_point_t
	{
	public:
		constexpr fixed_point_t() noexcept;
		constexpr explicit fixed_point_t(t const& v) noexcept;
		constexpr fixed_point_t(mk::fixed_point_t<t, n> const& other) noexcept;
		constexpr fixed_point_t(mk::fixed_point_t<t, n>&& other) noexcept;
		constexpr mk::fixed_point_t<t, n>& operator=(mk::fixed_point_t<t, n> const& other) noexcept;
		constexpr mk::fixed_point_t<t, n>& operator=(mk::fixed_point_t<t, n>&& other) noexcept;
		~fixed_point_t() noexcept = default;
		constexpr void swap(mk::fixed_point_t<t, n>& other) noexcept;
		[[nodiscard]] constexpr t const& get() const noexcept;
		constexpr void set(t const& v) noexcept;
	public:
		[[nodiscard]] static constexpr fixed_point_t<t, n> minimum() noexcept;
		[[nodiscard]] static constexpr fixed_point_t<t, n> maximum() noexcept;
		[[nodiscard]] static constexpr fixed_point_t<t, n> step() noexcept;
	private:
		t m_value;
	};


	template<typename t, unsigned n> inline void constexpr swap(mk::fixed_point_t<t, n>& a, mk::fixed_point_t<t, n>& b) noexcept { a.swap(b); }
	template<typename t, unsigned n> inline constexpr t const& get(mk::fixed_point_t<t, n> const& obj) noexcept { return obj.get(); }
	template<typename t, unsigned n> inline constexpr void set(mk::fixed_point_t<t, n>& obj, t const& val) noexcept { obj.set(val); }

	template<typename t, unsigned n> inline constexpr bool operator==(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept { return a.get() == b.get(); }
	template<typename t, unsigned n> inline constexpr bool operator!=(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept { return !(a == b); }

	template<typename t, unsigned n> constexpr mk::fixed_point_t<t, n> operator+(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept;
	template<typename t, unsigned n> constexpr mk::fixed_point_t<t, n> operator-(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept;
	template<typename t, unsigned n> constexpr mk::fixed_point_t<t, n> operator*(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept;
	template<typename t, unsigned n> constexpr mk::fixed_point_t<t, n> operator/(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept;

	template<typename f, typename t, unsigned n> [[nodiscard]] constexpr f to_floating_point(mk::fixed_point_t<t, n> const& obj) noexcept;
	template<typename t, unsigned n, typename f> [[nodiscard]] constexpr mk::fixed_point_t<t, n> from_floating_point(f const& flt) noexcept;
	

}

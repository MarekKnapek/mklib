#include "mk_fixed_point.hpp"

#include "mk_type_traits.hpp" // mk::make_signed_t, mk::make_bigger_t
#include "mk_utility.hpp" // mk::move


namespace mk
{


	template<unsigned n>
	struct pow2_t
	{
		static constexpr unsigned __int64 const value = 2 * pow2_t<n - 1>::value;
	};

	template<>
	struct pow2_t<0>
	{
		static constexpr unsigned __int64 const value = 1;
	};


	template<typename f>
	f floor(f const& flt) noexcept;

	template<typename t>
	t abs(t const& x) noexcept;

	template<typename t>
	typename mk::make_signed_t<t>::type unsigned_integer_distance(t const& a, t const& b) noexcept;


}


template<typename f>
f mk::floor(f const& flt) noexcept
{
	signed __int64 const integer = static_cast<signed __int64>(flt);
	f const flt_2 = static_cast<f>(integer);
	if (flt_2 == flt || flt >= static_cast<f>(0.0))
	{
		return flt_2;
	}
	else
	{
		return flt_2 - static_cast<f>(1.0);
	}
}

template<typename t>
t mk::abs(t const& x) noexcept
{
	return x < static_cast<t>(0) ? -x : x;
}

template<typename t>
typename mk::make_signed_t<t>::type mk::unsigned_integer_distance(t const& a, t const& b) noexcept
{
	return static_cast<typename mk::make_signed_t<t>::type>(a - b);
}


template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>::fixed_point_t() noexcept :
	m_value()
{
	static_assert(n < sizeof(t) * 8 - 1, "");
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>::fixed_point_t(t const& v) noexcept :
	m_value(v)
{
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>::fixed_point_t(mk::fixed_point_t<t, n> const& other) noexcept :
	m_value(other.m_value)
{
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>::fixed_point_t(mk::fixed_point_t<t, n>&& other) noexcept :
	m_value(mk::move(other))
{
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>& mk::fixed_point_t<t, n>::operator=(mk::fixed_point_t<t, n> const& other) noexcept
{
	m_value = other.m_value;
	return *this;
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n>& mk::fixed_point_t<t, n>::operator=(mk::fixed_point_t<t, n>&& other) noexcept
{
	m_value = mk::move(other.m_value);
	return *this;
}

template<typename t, unsigned n>
constexpr void mk::fixed_point_t<t, n>::swap(mk::fixed_point_t<t, n>& other) noexcept
{
	t tmp = m_value;
	m_value = other.m_value;
	other.m_value = tmp;
}

template<typename t, unsigned n>
[[nodiscard]] constexpr t const& mk::fixed_point_t<t, n>::get() const noexcept
{
	return m_value;
}

template<typename t, unsigned n>
constexpr void mk::fixed_point_t<t, n>::set(t const& v) noexcept
{
	m_value = v;
}

template<typename t, unsigned n>
[[nodiscard]] constexpr mk::fixed_point_t<t, n> mk::fixed_point_t<t, n>::minimum() noexcept
{
	static constexpr unsigned const m = static_cast<unsigned>(sizeof(t) * 8 - n - 1);
	static constexpr t const pow_mn = static_cast<t>(mk::pow2_t<m + n>::value);
	static constexpr t const fxd_min = static_cast<t>(pow_mn);

	return mk::fixed_point_t<t, n>{fxd_min};
}

template<typename t, unsigned n>
[[nodiscard]] constexpr mk::fixed_point_t<t, n> mk::fixed_point_t<t, n>::maximum() noexcept
{
	static constexpr unsigned const m = static_cast<unsigned>(sizeof(t) * 8 - n - 1);
	static constexpr t const pow_mn = static_cast<t>(mk::pow2_t<m + n>::value);
	static constexpr t const fxd_max = static_cast<t>(pow_mn - 1);

	return mk::fixed_point_t<t, n>{fxd_max};
}

template<typename t, unsigned n>
[[nodiscard]] constexpr mk::fixed_point_t<t, n> mk::fixed_point_t<t, n>::step() noexcept
{
	return mk::fixed_point_t<t, n>{1};
}


template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n> mk::operator+(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept
{
	static constexpr unsigned const all_bits = static_cast<unsigned>(sizeof(t) * 8);
	static constexpr t const mask = static_cast<t>(mk::pow2_t<all_bits>::value - 1);

	t const aa = a.get();
	t const bb = b.get();
	t const cc = static_cast<t>((aa + bb) & mask);
	return mk::fixed_point_t<t, n>{cc};
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n> mk::operator-(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept
{
	static constexpr unsigned const all_bits = static_cast<unsigned>(sizeof(t) * 8);
	static constexpr t const mask = static_cast<t>(mk::pow2_t<all_bits>::value - 1);

	t const aa = a.get();
	t const bb = b.get();
	t const cc = static_cast<t>((aa - bb) & mask);
	return mk::fixed_point_t<t, n>{cc};
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n> mk::operator*(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept
{
	typedef typename mk::make_signed_t<t>::type signed_t;
	typedef typename mk::make_bigger_t<signed_t>::type bigger_t;

	static constexpr signed_t const pow = static_cast<signed_t>(mk::pow2_t<n>::value);
	static constexpr unsigned const all_bits = static_cast<unsigned>(sizeof(t) * 8);
	static constexpr t const mask = static_cast<t>(mk::pow2_t<all_bits>::value - 1);

	bigger_t const aa = static_cast<bigger_t>(static_cast<signed_t>(a.get()));
	bigger_t const bb = static_cast<bigger_t>(static_cast<signed_t>(b.get()));
	bigger_t const cc = static_cast<bigger_t>(aa * bb);
	bigger_t const dd = static_cast<bigger_t>(cc / pow);
	
	t const ret = static_cast<t>(dd & mask);
	return mk::fixed_point_t<t, n>{ret};
}

template<typename t, unsigned n>
constexpr mk::fixed_point_t<t, n> mk::operator/(mk::fixed_point_t<t, n> const& a, mk::fixed_point_t<t, n> const& b) noexcept
{
	typedef typename mk::make_signed_t<t>::type signed_t;
	typedef typename mk::make_bigger_t<signed_t>::type bigger_t;

	static constexpr signed_t const pow = static_cast<signed_t>(mk::pow2_t<n>::value);
	static constexpr unsigned const all_bits = static_cast<unsigned>(sizeof(t) * 8);
	static constexpr t const mask = static_cast<t>(mk::pow2_t<all_bits>::value - 1);

	if(b.get() == 0)
	{
		if(a.get() < 0)
		{
			return mk::fixed_point_t<t, n>::minimum();
		}
		else
		{
			return mk::fixed_point_t<t, n>::maximum();
		}
	}

	bigger_t const aa = static_cast<bigger_t>(static_cast<signed_t>(a.get()));
	bigger_t const bb = static_cast<bigger_t>(static_cast<signed_t>(b.get()));
	bigger_t const cc = static_cast<bigger_t>(aa * pow);
	bigger_t const dd = static_cast<bigger_t>(cc / bb);

	t const ret = static_cast<t>(dd & mask);
	return mk::fixed_point_t<t, n>{ret};
}

template<typename f, typename t, unsigned n>
[[nodiscard]] constexpr f mk::to_floating_point(mk::fixed_point_t<t, n> const& obj) noexcept
{
	typedef typename mk::make_signed_t<t>::type signed_t;

	/* static */ constexpr t const pow = static_cast<t>(mk::pow2_t<n>::value);
	/* static */ constexpr signed_t const signed_pow = static_cast<signed_t>(pow);
	/* static */ constexpr t const mask = static_cast<t>(mk::pow2_t<n>::value - 1);
	/* static */ constexpr t const inverted_mask = static_cast<t>(~mask);

	t const fxd = obj.get();

	t const before_point_bits = static_cast<t>(fxd & inverted_mask);
	signed_t const before_point_signed_bits = static_cast<signed_t>(before_point_bits);
	signed_t const before_point_signed_int = static_cast<signed_t>(before_point_signed_bits / signed_pow);
	t const after_point_bits = static_cast<t>(fxd & mask);

	double const flt = static_cast<f>(before_point_signed_int) + static_cast<f>(after_point_bits) / static_cast<f>(pow);
	return flt;
}

template<typename t, unsigned n, typename f>
[[nodiscard]] constexpr mk::fixed_point_t<t, n> mk::from_floating_point(f const& flt) noexcept
{
	typedef typename mk::make_signed_t<t>::type signed_t;

	static constexpr t const pow = static_cast<t>(mk::pow2_t<n>::value);
	static constexpr signed_t const pows = static_cast<signed_t>(pow);
	static constexpr f const powf = static_cast<f>(pow);
	static constexpr t const mask = static_cast<t>(pow - 1);
	static constexpr unsigned const m = static_cast<unsigned>(sizeof(t) * 8 - n - 1);
	static constexpr t const pow_m = static_cast<t>(mk::pow2_t<m>::value);
	static constexpr f const flt_min = -static_cast<f>(pow_m);
	static constexpr t const pow_mn = static_cast<t>(mk::pow2_t<m + n>::value);
	static constexpr t const mask_a = static_cast<t>(mk::pow2_t<m + n + 1>::value - 1);
	static constexpr t const fxd_min = static_cast<t>(pow_mn);
	static constexpr f const one = static_cast<f>(1.0);
	static constexpr f const flt_max = static_cast<f>(pow_m) - one / static_cast<f>(pow);
	static constexpr t const fxd_max = static_cast<t>(pow_mn - 1);

	if(flt <= flt_min)
	{
		return mk::fixed_point_t<t, n>{fxd_min};
	}
	if(flt >= flt_max)
	{
		return mk::fixed_point_t<t, n>{fxd_max};
	}

	t const after_point_bits = static_cast<t>((flt - mk::floor(flt)) * powf);
	signed_t const before_point_signed_int = static_cast<signed_t>(mk::floor(flt));
	signed_t const before_point_signed_bits = static_cast<signed_t>(before_point_signed_int * pows);
	t const before_point_bits = static_cast<t>(before_point_signed_bits);

	t const res_1 = static_cast<t>(before_point_bits | after_point_bits);
	t const res_2 = static_cast<t>((res_1 + 1) & mask_a);
	f const flt_1 = mk::to_floating_point<f>(mk::fixed_point_t<t, n>{res_1});
	f const flt_2 = mk::to_floating_point<f>(mk::fixed_point_t<t, n>{res_2});
	t const res = mk::abs(flt - flt_1) < mk::abs(flt - flt_2) ? res_1 : res_2;
	return mk::fixed_point_t<t, n>{res};
}





namespace mk
{
	namespace test
	{

		template<typename t, unsigned n>
		struct test2_impl_t
		{
			static void test_constexpr();
			static void test_1();
			template<typename op> static void test_2();
			template<typename op> static void test_3();
			static void test_4();
			static void impl();
		};

		template<typename t, unsigned n, bool b>
		struct test2_base_t
		{
			static void run();
		};

		template<typename t, unsigned n>
		struct test2_base_t<t, n, true>
		{
			static void run();
		};

		template<typename t, unsigned n>
		struct test2_t
		{
			static void run();
		};


		template<typename t>
		struct test1_t
		{
			static void run();
		};


		void run();


	}
}


#define _ALLOW_RTCc_IN_STL
#include <random>
#include <limits>

extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(char const*);

void print_float(double const& flt)
{
	char buff[128];
	snprintf(buff, sizeof(buff), "%.50e\n", flt);
	OutputDebugStringA(buff);
}

void print_fixed(unsigned const& flt)
{
	char buff[128];
	snprintf(buff, sizeof(buff), "%u\n", flt);
	OutputDebugStringA(buff);
}

std::mt19937* g_mt;


template<typename t, unsigned n>
void mk::test::test2_impl_t<t, n>::test_constexpr()
{
	constexpr mk::fixed_point_t<t, n> const a{3};
	constexpr mk::fixed_point_t<t, n> const b{7};
	constexpr mk::fixed_point_t<t, n> const op_add = a + b;
	constexpr mk::fixed_point_t<t, n> const op_sub = a - b;
	constexpr mk::fixed_point_t<t, n> const op_mul = a * b;
	constexpr mk::fixed_point_t<t, n> const op_div = a / b;

	constexpr mk::fixed_point_t<t, n> const c = mk::from_floating_point<t, n>(9.0);
	constexpr double const d = mk::to_floating_point<double>(c);
}

template<typename t, unsigned n>
void mk::test::test2_impl_t<t, n>::test_1()
{
	static constexpr unsigned nn = sizeof(t) * 8;
	static constexpr unsigned mask = static_cast<unsigned>(mk::pow2_t<nn>::value - 1);

	std::uniform_int_distribution<unsigned> dist{std::numeric_limits<unsigned>::min(), std::numeric_limits<unsigned>::max()};
	for(int i = 0; i != 1'000'000; ++i)
	{
		unsigned const rnd = dist(*g_mt);
		mk::fixed_point_t<t, n> const fxd{static_cast<t>(rnd & mask)};
		double const flt = mk::to_floating_point<double>(fxd);
		if(!(mk::from_floating_point<t, n>(flt) == fxd))
		{
			__debugbreak();
		}
	}
}

template<typename t, unsigned n>
template<typename op>
void mk::test::test2_impl_t<t, n>::test_2()
{
	static constexpr unsigned nn = sizeof(t) * 8;
	static constexpr unsigned mask = static_cast<unsigned>(mk::pow2_t<nn>::value - 1);

	std::uniform_int_distribution<unsigned> dist{std::numeric_limits<unsigned>::min(), std::numeric_limits<unsigned>::max()};
	for(int i = 0; i != 1'000'000; ++i)
	{
		unsigned const rnd_1 = dist(*g_mt);
		unsigned const rnd_2 = dist(*g_mt);

		mk::fixed_point_t<t, n> const fxd_1{static_cast<t>(rnd_1 & mask)};
		mk::fixed_point_t<t, n> const fxd_2{static_cast<t>(rnd_2 & mask)};

		double const flt_1 = mk::to_floating_point<double>(fxd_1);
		double const flt_2 = mk::to_floating_point<double>(fxd_2);

		mk::fixed_point_t<t, n> fxd_res;
		double flt_res;
		
		fxd_res = op{}(fxd_1, fxd_2);
		flt_res = op{}(flt_1, flt_2);

		if(flt_res >= mk::to_floating_point<double>(mk::fixed_point_t<t, n>::minimum()) && flt_res <= mk::to_floating_point<double>(mk::fixed_point_t<t, n>::maximum()))
		{
			if(!(mk::to_floating_point<double>(fxd_res) == flt_res))
			{
				__debugbreak();
			}
			if(!(fxd_res == mk::from_floating_point<t, n>(flt_res)))
			{
				__debugbreak();
			}
		}
	}
}

template<typename t, unsigned n>
template<typename op>
void mk::test::test2_impl_t<t, n>::test_3()
{
	static constexpr unsigned nn = sizeof(t) * 8;
	static constexpr unsigned mask = static_cast<unsigned>(mk::pow2_t<nn>::value - 1);
	static constexpr double const step = mk::to_floating_point<double>(mk::fixed_point_t<t, n>::step());

	std::uniform_int_distribution<unsigned> dist{std::numeric_limits<unsigned>::min(), std::numeric_limits<unsigned>::max()};
	for(int i = 0; i != 1'000'000; ++i)
	{
		unsigned const rnd_1 = dist(*g_mt);
		unsigned const rnd_2 = dist(*g_mt);

		mk::fixed_point_t<t, n> const fxd_1{static_cast<t>(rnd_1 & mask)};
		mk::fixed_point_t<t, n> const fxd_2{static_cast<t>(rnd_2 & mask)};

		double const flt_1 = mk::to_floating_point<double>(fxd_1);
		double const flt_2 = mk::to_floating_point<double>(fxd_2);

		mk::fixed_point_t<t, n> fxd_res;
		double flt_res;

		fxd_res = op{}(fxd_1, fxd_2);
		flt_res = op{}(flt_1, flt_2);

		if(flt_res >= mk::to_floating_point<double>(mk::fixed_point_t<t, n>::minimum()) && flt_res <= mk::to_floating_point<double>(mk::fixed_point_t<t, n>::maximum()))
		{
			if(!(mk::abs(mk::to_floating_point<double>(fxd_res) - flt_res) <= step))
			{
				__debugbreak();
			}
			if(!(mk::unsigned_integer_distance(fxd_res.get(), mk::from_floating_point<t, n>(flt_res).get()) <= 1))
			{
				__debugbreak();
			}
		}
	}
}

template<typename t, unsigned n>
void mk::test::test2_impl_t<t, n>::test_4()
{
	static constexpr double const step = mk::to_floating_point<double>(mk::fixed_point_t<t, n>::step());

	std::uniform_real_distribution<double> dist
	{
		mk::to_floating_point<double>(mk::fixed_point_t<t, n>::minimum()) - 10.0,
		mk::to_floating_point<double>(mk::fixed_point_t<t, n>::maximum()) + 10.0
	};
	for(int i = 0; i != 1'000'000; ++i)
	{
		double const flt = dist(*g_mt);
		mk::fixed_point_t<t, n> const fxd = mk::from_floating_point<t, n>(flt);
		if(flt < mk::to_floating_point<double>(mk::fixed_point_t<t, n>::minimum()))
		{
			if(!(fxd == mk::fixed_point_t<t, n>::minimum()))
			{
				__debugbreak();
			}
		}
		else if(flt > mk::to_floating_point<double>(mk::fixed_point_t<t, n>::maximum()))
		{
			if(!(fxd == mk::fixed_point_t<t, n>::maximum()))
			{
				__debugbreak();
			}
		}
		else
		{
			if(!(mk::abs(mk::to_floating_point<double>(fxd) - flt) < step))
			{
				__debugbreak();
			}
		}
	}
}

struct operation_add_t { template<typename tt> tt operator()(tt const& a, tt const& b) noexcept { return a + b; } };
struct operation_sub_t { template<typename tt> tt operator()(tt const& a, tt const& b) noexcept { return a - b; } };
struct operation_mul_t { template<typename tt> tt operator()(tt const& a, tt const& b) noexcept { return a * b; } };
struct operation_div_t { template<typename tt> tt operator()(tt const& a, tt const& b) noexcept { return a / b; } };

template<typename t, unsigned n>
void mk::test::test2_impl_t<t, n>::impl()
{
	test_1();
	test_2<operation_add_t>();
	test_2<operation_sub_t>();
	test_3<operation_mul_t>();
	test_3<operation_div_t>();
	test_4();
}

template<typename t, unsigned n, bool b>
void mk::test::test2_base_t<t, n, b>::run()
{
	mk::test::test2_base_t<t, n - 1, n - 1 == 1>::run();
	mk::test::test2_impl_t<t, n>::impl();
}

template<typename t, unsigned n>
void mk::test::test2_base_t<t, n, true>::run()
{
	mk::test::test2_impl_t<t, n>::impl();
}

template<typename t, unsigned n>
void mk::test::test2_t<t, n>::run()
{
	mk::test::test2_base_t<t, n, false>::run();
}


template<typename t>
void mk::test::test1_t<t>::run()
{
	mk::test::test2_t<t, sizeof(t) * 8 - 2>::run();
}


void mk::test::run()
{
	g_mt = new std::mt19937{std::random_device{}()};

	mk::test::test1_t<unsigned __int8>::run();
	mk::test::test1_t<unsigned __int16>::run();
	mk::test::test1_t<unsigned __int32>::run();

	delete g_mt;
}


int fixed_point_test()
{
	for(int i = 0; i != 10; ++i)
	{
		mk::test::run();
	}
	std::exit(0);
}


static int xxx = fixed_point_test();

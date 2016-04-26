#include <functional>
#include <type_traits>
#include <utility>

template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
	: build_indices<N - 1, N - 1, Is...>
{
};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};

template<int I> struct placeholder {};

namespace std
{
	template<int I>
	struct is_placeholder< ::placeholder<I>> : std::integral_constant<int, I> {};
} // std::
namespace detail
{
	template<std::size_t... Is, class Ret, class Fn, class... MArgs, class... Args>
	auto easy_bind(indices<Is...>, Ret(Fn::*f)(MArgs...), Fn *i, Args&&... args)
		-> decltype(std::bind(f, i, std::forward<Args>(args)..., placeholder<1 + Is>{}...))
	{
		return std::bind(f, i, std::forward<Args>(args)..., placeholder<1 + Is>{}...);
	}
}

template<class Ret, class... FArgs, class Fn, class... MArgs, class... Args>
auto easy_bind(std::function<Ret(FArgs...)>, Ret(Fn::*f)(MArgs...), Fn *i, Args&&... args)
-> decltype(detail::easy_bind(build_indices<sizeof...(FArgs)-sizeof...(Args)>{}, f, i, std::forward<Args>(args)...))
{

	return detail::easy_bind(build_indices<sizeof...(FArgs)-sizeof...(Args)>{}, f, i, std::forward<Args>(args)...);
}

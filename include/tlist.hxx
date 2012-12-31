#ifndef MRR_MP_TLIST_HXX_
#define MRR_MP_TLIST_HXX_

#include <cstddef>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {
namespace mp {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename... Args>
struct tlist;

template <typename Arg, typename... Args>
struct tlist<Arg, Args...>
{
  using head_type = Arg;

  using tail_type = tlist<Arg, Args...>;
  static const std::size_t tail_size = sizeof...(Args);

  using type = tlist<Arg, Args...>;
  static const std::size_t size = 1 + tail_size;
};

template <typename Arg>
struct tlist<Arg>
{
  using head_type = Arg;

  using tail_type = tlist<>;
  static const std::size_t tail_size = 0;

  using type = tlist<Arg>;
  static const std::size_t size = 1;
};

template <>
struct tlist<>
{
  using tail_type =  tlist<>;
  static const std::size_t tail_size = 0;

  using type = tlist<>;
  static const std::size_t size = 0;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mp
} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_MP_TLIST_HXX_

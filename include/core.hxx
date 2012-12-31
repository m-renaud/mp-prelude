#ifndef MRR_MP_CORE_HXX_
#define MRR_MP_CORE_HXX_

#include <type_traits>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {
namespace mp {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename C1, typename C2>
struct divides
{
  using type = std::integral_constant<
    typename C1::value_type, C1::value / C2::value
  >;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename C1, typename C2>
struct plus
{
  using type = std::integral_constant<
    typename C1::value_type, C1::value + C2::value
  >;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename C1, typename C2>
struct minus
{
  using type = std::integral_constant<
    typename C1::value_type, C1::value - C2::value
  >;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename C1, typename C2>
struct multiplies
{
  using type = std::integral_constant<
    typename C1::value_type, C1::value * C2::value
  >;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mp
} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // #ifndef MRR_MP_CORE_HXX_

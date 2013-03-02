#ifndef MRR_MP_PRELUDE_HXX_
#define MRR_MP_PRELUDE_HXX_

//m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (c) 2012 Matt Renaud. All Rights Reserved.
//
// Email:  mrenaud92@gmail.com
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <type_traits>

#include "tlist.hxx"

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {
namespace mp {
namespace prelude {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Implemented functions:
//
// all
// and_
// any
// at (Not in Haskell's Prelude)
// concat
// drop
// elem
// foldl
// foldr
// fst
// head
// id
// init
// last
// length
// map
// negate
// notElem
// not_
// null
// or_
// replicate
// reverse
// tail
// take
// zip


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <template <typename> class Pred, typename Seq>     struct all_impl;
template <typename Seq>                                     struct and_impl;
template <template <typename> class Pred, typename Seq>     struct any_impl;
template <typename Seq, typename N>                         struct at_impl;
template <typename... Args>                                 struct concat_impl;
template <typename N, typename Seq>                         struct drop_impl;
template <typename Elem, typename Seq>                      struct elem_impl;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>                                                           struct foldl_impl;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>                                                           struct foldr_impl;

template <typename Pair>                                    struct fst_impl;
template <typename Seq>                                     struct head_impl;
template <typename T>                                       struct id_impl;
template <typename Seq>                                     struct init_impl;
template <typename Seq>                                     struct last_impl;
template <typename Seq>                                     struct length_impl;
template <template <typename> class Functor, typename Seq>  struct map_impl;
template <typename Number>                                  struct negate_impl;
template <typename Elem, typename Seq>                      struct not_elem_impl;
template <typename Constant>                                struct not_impl;
template <typename Seq>                                     struct null_impl;
template <typename Seq>                                     struct or_impl;
template <typename N, typename T>                           struct replicate_impl;
template <typename Seq>                                     struct reverse_impl;
template <typename Seq>                                     struct tail_impl;
template <typename N, typename Seq>                         struct take_impl;
template <typename SeqOne, typename SeqTwo>                 struct zip_impl;




//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Template aliases...

template <template <typename> class Pred, typename Seq>
using all = typename all_impl<Pred,Seq>::type;

template <typename Seq>
using and_ = typename and_impl<Seq>::type;

template <template <typename> class Pred, typename Seq>
using any = typename any_impl<Pred,Seq>::type;

template <typename Seq, typename N>
using at = typename at_impl<Seq,N>::type;

template <typename... Args>
using concat = typename concat_impl<Args...>::type;

template <typename N, typename Seq>
using drop = typename drop_impl<N,Seq>::type;

template <typename Elem, typename Seq>
using elem = typename elem_impl<Elem,Seq>::type;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>
using foldl = typename foldl_impl<BinFunc,A,Seq>::type;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>
using foldr = typename foldr_impl<BinFunc,A,Seq>::type;

template <typename Pair>
using fst = typename fst_impl<Pair>::type;

template <typename Seq>
using head = typename head_impl<Seq>::type;

template <typename T>
using id = typename id_impl<T>::type;

template <typename Seq>
using init = typename init_impl<Seq>::type;

template <typename Seq>
using last = typename last_impl<Seq>::type;

template <typename Seq>
using length = typename length_impl<Seq>::type;

template <template <typename> class Functor, typename Seq>
using map = typename map_impl<Functor,Seq>::type;

template <typename Number>
using negate = typename negate_impl<Number>::type;

template <typename Elem, typename Seq>
using not_elem = typename not_elem_impl<Elem,Seq>::type;

template <typename Constant>
using not_ = typename not_impl<Constant>::type;

template <typename Seq>
using null = typename null_impl<Seq>::type;

template <typename Seq>
using or_ = typename or_impl<Seq>::type;

template <typename N, typename T>
using replicate = typename replicate_impl<N,T>::type;

template <typename Seq>
using reverse = typename reverse_impl<Seq>::type;

template <typename Seq>
using tail = typename tail_impl<Seq>::type;

template <typename N, typename Seq>
using take = typename take_impl<N,Seq>::type;

template <typename SeqOne, typename SeqTwo>
using zip = typename zip_impl<SeqOne,SeqTwo>::type;


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace detail {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


// Prototypes
template <template <typename...> class T, typename... Args>
                                                      struct concat_wttp;
template <
  template <typename> class Functor,
  typename Ret,
  typename Seq
>
                                                      struct map_wetp;
template <typename Ret, typename N, typename T>       struct replicate_wetp;
template <typename Ret, typename Seq>                 struct reverse_wetp;
template <typename N, typename Ret, typename Seq>     struct take_wetp;
template <typename Ret, typename Seq1, typename Seq2> struct zip_wetp;



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <template <typename...> class T, typename... Args>
struct concat_wttp;

// Case where A and B are class templates...
template <
  template <typename...> class T,
  template <typename...> class A, typename... AArgs,
  template <typename...> class B, typename... BArgs,
  typename... Rest
>
struct concat_wttp<T, A<AArgs...>, B<BArgs...>, Rest...>
{
  using type = typename
    concat_wttp<
      T, T<AArgs..., BArgs...>, Rest...
    >::type
  ;
};

// Case where A but not B is a class templates...
template <
  template <typename...> class T,
  template <typename...> class A, typename... AArgs,
  typename B,
  typename... Rest
>
struct concat_wttp<T, A<AArgs...>, B, Rest...>
{
  using type = typename
    concat_wttp<
      T, T<AArgs...>, Rest...
    >::type
  ;
};

// Case where B but not A is a class templates...
template <
  template <typename...> class T,
  typename A,
  template <typename...> class B, typename... BArgs,
  typename... Rest
>
struct concat_wttp<T, A, B<BArgs...>,  Rest...>
{
  using type = typename
    concat_wttp<
      T, T<BArgs...>, Rest...
    >::type
  ;
};


// Case where neither A nor B are class templates...
template <
  template <typename...> class T,
  typename A,
  typename B,
  typename... Rest
>
struct concat_wttp<T,A,B, Rest...>
{
  using type = typename
    concat_wttp<
      T, Rest...
    >::type
  ;
};

// Base Case where A is a class template...
template <
  template <typename...> class T,
  template <typename...> class A, typename... AArgs
>
struct concat_wttp<T, A<AArgs...>>
{
  using type = T<AArgs...>;
};

// Base Case where A is not a class template...
template <
  template <typename...> class T,
  typename A
>
struct concat_wttp<T,A>
{
  using type = T<>;
};

// Base Case where there are no types...
template <template <typename...> class T>
struct concat_wttp<T>
{
  using type = T<>;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
// map_wetp
//
template <
  template <typename> class Functor,
  typename Ret,
  typename Seq
>
struct map_wetp;


template <
  template <typename> class Functor,
  typename Ret,
  template <typename...> class SeqHolder
>
struct map_wetp<Functor, Ret, SeqHolder<>>
{
  using type = Ret;
};



template <
  template <typename> class Functor,
  template <typename...> class RetHolder,
  typename... RetArgs,
  template <typename...> class SeqHolder,
  typename Arg,
  typename... Args
>
struct map_wetp<Functor, RetHolder<RetArgs...>, SeqHolder<Arg,Args...>>
{
  using type = typename
    map_wetp<
      Functor,
      RetHolder<RetArgs..., typename Functor<Arg>::type>,
      SeqHolder<Args...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Ret, typename N, typename T>
struct replicate_wetp;

// Recursive case: Still need to replicate type N more times
template <
  template <typename...> class Ret, typename... RetVals,
  std::size_t N,
  typename T
>
struct replicate_wetp<Ret<RetVals...>, std::integral_constant<std::size_t, N>, T>
{
  using type = typename
    replicate_wetp<
      Ret<RetVals..., T>, std::integral_constant<std::size_t, N-1>, T
    >::type
  ;
};

// Base case:
template <
  template <typename...> class Ret, typename... RetVals,
  typename T
>
struct replicate_wetp<Ret<RetVals...>, std::integral_constant<std::size_t, 0>, T>
{
  using type = Ret<RetVals...>;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Recursive case: More elements to reverse
template <typename Ret, typename Seq>
struct reverse_wetp;

template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq,
  typename Arg,
  typename... Args
>
struct reverse_wetp<Ret<RetVals...>, Seq<Arg, Args...>>
{
  using type = typename
    reverse_wetp<
      Ret<Arg, RetVals...>,
      Seq<Args...>
    >::type
  ;
};

// Base case: No more elements to reverse
template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq
>
struct reverse_wetp<Ret<RetVals...>, Seq<>>
{
  using type = Ret<RetVals...>;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename N, typename Ret, typename Seq>
struct take_wetp;

template <
  std::size_t N,
  template <typename...> class Ret,
  typename... RetVals,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct take_wetp<
  std::integral_constant<std::size_t, N>,
  Ret<RetVals...>,
  Seq<Head, Tail...>
>
{
  using type = typename
    take_wetp<
      std::integral_constant<std::size_t, N-1>,
      Ret<RetVals..., Head>,
      Seq<Tail...>
    >::type
  ;
};

// Base case: Take 1
template <
  template <typename...> class Ret,
  typename... RetVals,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct take_wetp <
  std::integral_constant<std::size_t, 1>,
  Ret<RetVals...>,
  Seq<Head, Tail...>
>
{
  using type = typename Ret<RetVals..., Head>::type;
};

// take 0
template <
  template <typename...> class Ret,
  typename... RetVals,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct take_wetp <
  std::integral_constant<std::size_t, 0>,
  Ret<RetVals...>,
  Seq<Head, Tail...>
>
{
  using type = typename Ret<>::type;
};




//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Ret, typename Seq1, typename Seq2>
struct zip_wetp;


// Case where there is at least one argument in Seq1 and Seq2...
template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq1, typename Arg1, typename... Args1,
  template <typename...> class Seq2, typename Arg2, typename... Args2
>
struct zip_wetp<
  Ret<RetVals...>,
  Seq1<Arg1, Args1...>,
  Seq2<Arg2, Args2...>
>
{
  using type = typename
    zip_wetp<
      Ret<RetVals..., Ret<Arg1, Arg2>>,
      Seq1<Args1...>,
      Seq2<Args2...>
    >::type
  ;
};

// Case where there are no arguments in Seq1...
template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq1,
  template <typename...> class Seq2, typename... Args2
>
struct zip_wetp<
  Ret<RetVals...>,
  Seq1<>,
  Seq2<Args2...>
>
{
  using type = Ret<RetVals...>;
};

// Case where there are no arguments in Seq2...
template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq1, typename... Args1,
  template <typename...> class Seq2
>
struct zip_wetp<
  Ret<RetVals...>,
  Seq1<Args1...>,
  Seq2<>
>
{
  using type = Ret<RetVals...>;
};

// Case where neither have arguments...
template <
  template <typename...> class Ret, typename... RetVals,
  template <typename...> class Seq1,
  template <typename...> class Seq2
>
struct zip_wetp<
  Ret<RetVals...>,
  Seq1<>,
  Seq2<>
>
{
  using type = Ret<RetVals...>;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace detail

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  all
//

template <template <typename> class Pred, typename Seq>
struct all_impl;


template <template <typename> class Pred, typename Seq>
struct all_impl
{
  using type = std::true_type;
};

template <
  template <typename> class Pred,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct all_impl<Pred, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      Pred<Head>::type::value,
      all<Pred, Seq<Tail...>>,
      std::false_type
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  and_
//

template <typename Seq>
struct and_impl;


template <typename Seq>
struct and_impl
{
  using type = std::true_type;
};

template <
  template <typename...> class Seq,
  typename... Tail
>
struct and_impl<Seq<std::false_type, Tail...>>
{
  using type = std::false_type;
};

template <
  template <typename...> class Seq,
  typename... Tail
>
struct and_impl<Seq<std::true_type, Tail...>>
{
  using type = and_<Seq<Tail...>>;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  any_impl
//

template <template <typename> class Pred, typename Seq>
struct any_impl;


template <template <typename> class Pred, typename Seq>
struct any_impl
{
  using type = typename std::false_type::type;
};

template <
  template <typename> class Pred,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct any_impl<Pred, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      Pred<Head>::type::value,
      std::true_type,
      any<Pred, Seq<Tail...>>
    >::type
  ;

};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  at_impl
//

template <typename Seq, typename N>
struct at_impl;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail,
  std::size_t N
>
struct at_impl<Seq<Head, Tail...>, std::integral_constant<std::size_t, N>>
{
  using type = typename
    at_impl<
      Seq<Tail...>,
      std::integral_constant<std::size_t, N-1>
    >::type
  ;
};

template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct at_impl<Seq<Head, Tail...>, std::integral_constant<std::size_t, 0>>
{
  using type = Head;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  concat_impl
//

template <typename... Args>
struct concat_impl;


template <typename... Args>
struct concat_impl
{
  using type = typename detail::concat_wttp<tlist, Args...>::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  drop_impl
//

template <typename N, typename Seq>
struct drop_impl;


// Base case: No more elements in the typelist
template <
  std::size_t N,
  template <typename...> class Seq
>
struct drop_impl<std::integral_constant<std::size_t, N>, Seq<>>
{
  using type = Seq<>;
};


// Base case: N == 0
template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct drop_impl<std::integral_constant<std::size_t, 0>, Seq<Head,Tail...>>
{
  using type = Seq<Head,Tail...>;
};


// Recursive case: More elements to drop
template <
  std::size_t N,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct drop_impl<std::integral_constant<std::size_t, N>, Seq<Head, Tail...>>
{
  using type = typename
    drop_impl<
      std::integral_constant<std::size_t, N-1>, Seq<Tail...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  elem_impl
//

template <typename Elem, typename Seq>
struct elem_impl;


// Base case:
template <
  typename Elem,
  template <typename...> class Seq
>
struct elem_impl<Elem, Seq<>>
{
  using type = std::false_type;
};

// Recursive case:
template <
  typename Elem,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct elem_impl<Elem, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      (Elem::value == Head::value),
      std::true_type,
      elem<Elem, Seq<Tail...>>
    >::type
  ;
};




//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  foldl_impl
//

template <template<typename , typename> class BinFunc, typename A, typename Seq>
struct foldl_impl;


// Base Case: No more elements in the sequence.
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq
>
struct foldl_impl<
  BinaryFunc,
  CurVal,
  Seq<>
>
{
  using type = CurVal;
};


// Recursive Case:
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq,
  typename Val,
  typename... Args
>
struct foldl_impl<
  BinaryFunc,
  CurVal,
  Seq<Val, Args...>
>
{
  using type = typename
    foldl_impl<
      BinaryFunc,
      typename BinaryFunc<CurVal, Val>::type,
      Seq<Args...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  foldr_impl
//

template <template<typename , typename> class BinFunc, typename A, typename Seq>
struct foldr_impl;


// Base Case: No more elements in the sequence.
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq
>
struct foldr_impl<
  BinaryFunc,
  CurVal,
  Seq<>
>
{
  using type = CurVal;
};


// Recursive Case:
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq,
  typename Val,
  typename... Args
>
struct foldr_impl<
  BinaryFunc,
  CurVal,
  Seq<Val, Args...>
>
{
  using type = typename
    BinaryFunc<
      Val,
      foldr<BinaryFunc, CurVal, Seq<Args...>>
    >::type
  ;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  fst_impl
//

template <typename Pair>
struct fst_impl;


template <
  template <typename...> class Pair,
  typename First,
  typename Second
>
struct fst_impl<Pair<First, Second>>
{
  using type = First;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  head_impl
//

template <typename Seq>
struct head_impl;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct head_impl<Seq<Head, Tail...>>
{
  using type = Head;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  id_impl
//

template <typename T>
struct id_impl;


template <typename T>
struct id_impl
{
  using type = T;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  init_impl
//

template <typename Seq>
struct init_impl;


template <
  template <typename...> class Seq,
  typename... Args
>
struct init_impl<Seq<Args...>>
{
  static_assert(
    sizeof...(Args) > 0,
    "Not enough args given to prelude::init!"
  );

  using type = typename
    take_impl<
      std::integral_constant<std::size_t, sizeof...(Args) - 1>, Seq<Args...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  last_impl
//

template <typename Seq>
struct last_impl;


template <
  template <typename...> class Seq,
  typename... Args
>
struct last_impl<Seq<Args...>>
{
  static_assert(
    sizeof...(Args) > 0,
    "Not enough args given to prelude::last!"
  );

  using type = typename
    at_impl<
      Seq<Args...>,
      std::integral_constant<std::size_t, sizeof...(Args) - 1>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  length_impl
//

template <typename Seq>
struct length_impl;


template <
  template <typename...> class Seq,
  typename... Args
>
struct length_impl<Seq<Args...>>
{
  using type = typename
    std::integral_constant<std::size_t, sizeof...(Args)>::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  map_impl
//

template <template <typename> class Functor, typename Seq>
struct map_impl;


template <
  template <typename> class Functor,
  typename Seq
>
struct map_impl
{
  using type = typename detail::map_wetp<Functor,tlist<>,Seq>::type;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  negate_impl
//

template <typename Number>
struct negate_impl;


template <
  typename NumType,
  NumType value
>
struct negate_impl<std::integral_constant<NumType, value>>
{
private:
  using SignedNumType = typename std::make_signed<NumType>::type;

public:
  using type =
    std::integral_constant<
      SignedNumType,
      static_cast<SignedNumType>(-value)
    >
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  not_elem_impl
//

template <typename Elem, typename Seq>
struct not_elem_impl;


template <typename Elem, typename Seq>
struct not_elem_impl
{
  using type = not_<elem<Elem,Seq>>;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  not_impl
//

template <typename Constant>
struct not_impl;


template <>
struct not_impl<std::true_type>
{
  using type = std::false_type;
};

template <>
struct not_impl<std::false_type>
{
  using type = std::true_type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  null_impl
//

template <typename Seq>
struct null_impl;


template <typename Seq>
struct null_impl
{
  using type = std::true_type;
};

template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct null_impl<Seq<Head,Tail...>>
{
  using type = std::false_type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  or_impl
//

template <typename Seq>
struct or_impl;


// Base case: No more elements meaning they must have all been false
template <typename Seq>
struct or_impl
{
  using type = std::false_type;
};

// Base case: True encountered, making the ``or" true
template <
  template <typename...> class Seq,
  typename... Tail
>
struct or_impl<Seq<std::true_type, Tail...>>
{
  using type = std::true_type;
};

// Recursive case: False encountered, continue for the rest of the list
template <
  template <typename...> class Seq,
  typename... Tail
>
struct or_impl<Seq<std::false_type, Tail...>>
{
  using type = or_<Seq<Tail...>>;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  replicate_impl
//

template <typename N, typename T>
struct replicate_impl;


template <
  std::size_t N,
  typename T
>
struct replicate_impl<std::integral_constant<std::size_t, N>, T>
{
  using type = typename
    detail::replicate_wetp<
      tlist<>, std::integral_constant<std::size_t, N>, T
    >::type
  ;
};




//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  reverse_impl
//

template <typename Seq>
struct reverse_impl;


template <
  template <typename...> class Seq,
  typename... Args
>
struct reverse_impl<Seq<Args...>>
{
  using type = typename
    detail::reverse_wetp<
      Seq<>, Seq<Args...>
    >::type
  ;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  tail_impl
//

template <typename Seq>
struct tail_impl;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct tail_impl<Seq<Head, Tail...>>
{
  using type = typename tlist<Tail...>::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  take_impl
//

template <typename N, typename Seq>
struct take_impl;

template <
  typename SizeType,
  SizeType N,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct take_impl<std::integral_constant<SizeType, N>, Seq<Head, Tail...>>
{
  using type = typename
    detail::take_wetp<
      std::integral_constant<SizeType, N>, tlist<>, Seq<Head,Tail...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  zip_impl
//

template <typename SeqOne, typename SeqTwo>
struct zip_impl;


template <
  template <typename...> class Seq1, typename... Args1,
  template <typename...> class Seq2, typename... Args2
>
struct zip_impl<Seq1<Args1...>, Seq2<Args2...> >
{
  using type = typename
    detail::zip_wetp<tlist<>, Seq1<Args1...>, Seq2<Args2...> >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace prelude
} // namespace mp
} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_MP_PRELUDE_HXX_

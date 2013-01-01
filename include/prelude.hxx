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
template <template <typename> class Pred, typename Seq>     struct all;
template <typename Seq>                                     struct and_;
template <template <typename> class Pred, typename Seq>     struct any;
template <typename Seq, typename N>                         struct at;
template <typename... Args>                                 struct concat;
template <typename N, typename Seq>                         struct drop;
template <typename Elem, typename Seq>                      struct elem;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>                                                           struct foldl;

template <
  template<typename, typename> class BinFunc,
  typename A, typename Seq
>                                                           struct foldr;

template <typename Pair>                                    struct fst;
template <typename Seq>                                     struct head;
template <typename T>                                       struct id;
template <typename Seq>                                     struct init;
template <typename Seq>                                     struct last;
template <typename Seq>                                     struct length;
template <template <typename> class Functor, typename Seq>  struct map;
template <typename Number>                                  struct negate;
template <typename Elem, typename Seq>                      struct notElem;
template <typename Constant>                                struct not_;
template <typename Seq>                                     struct null;
template <typename Seq>                                     struct or_;
template <typename N, typename T>                           struct replicate;
template <typename Seq>                                     struct reverse;
template <typename Seq>                                     struct tail;
template <typename N, typename Seq>                         struct take;
template <typename SeqOne, typename SeqTwo>                 struct zip;


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
struct all;


template <template <typename> class Pred, typename Seq>
struct all
{
  using type = typename std::true_type::type;
};

template <
  template <typename> class Pred,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct all<Pred, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      Pred<Head>::type::value,
      typename all<Pred, Seq<Tail...>>::type,
      std::false_type
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  and_
//

template <typename Seq>
struct and_;


template <typename Seq>
struct and_
{
  using type = typename std::true_type::type;
};

template <
  template <typename...> class Seq,
  typename... Tail
>
struct and_<Seq<std::false_type, Tail...>>
{
  using type = typename std::false_type::type;
};

template <
  template <typename...> class Seq,
  typename... Tail
>
struct and_<Seq<std::true_type, Tail...>>
{
  using type = typename and_<Seq<Tail...>>::type;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  any
//

template <template <typename> class Pred, typename Seq>
struct any;


template <template <typename> class Pred, typename Seq>
struct any
{
  using type = typename std::false_type::type;
};

template <
  template <typename> class Pred,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct any<Pred, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      Pred<Head>::type::value,
      std::true_type,
      typename any<Pred, Seq<Tail...>>::type
    >::type
  ;

};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  at
//

template <typename Seq, typename N>
struct at;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail,
  std::size_t N
>
struct at<Seq<Head, Tail...>, std::integral_constant<std::size_t, N>>
{
  using type = typename
    at<
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
struct at<Seq<Head, Tail...>, std::integral_constant<std::size_t, 0>>
{
  using type = Head;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  concat
//

template <typename... Args>
struct concat;


template <typename... Args>
struct concat
{
  using type = typename detail::concat_wttp<tlist, Args...>::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  drop
//

template <typename N, typename Seq>
struct drop;


// Base case: No more elements in the typelist
template <
  std::size_t N,
  template <typename...> class Seq
>
struct drop<std::integral_constant<std::size_t, N>, Seq<>>
{
  using type = Seq<>;
};


// Base case: N == 0
template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct drop<std::integral_constant<std::size_t, 0>, Seq<Head,Tail...>>
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
struct drop<std::integral_constant<std::size_t, N>, Seq<Head, Tail...>>
{
  using type = typename
    drop<
      std::integral_constant<std::size_t, N-1>, Seq<Tail...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  elem
//

template <typename Elem, typename Seq>
struct elem;


// Base case:
template <
  typename Elem,
  template <typename...> class Seq
>
struct elem<Elem, Seq<>>
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
struct elem<Elem, Seq<Head, Tail...>>
{
  using type = typename
    std::conditional<
      (Elem::value == Head::value),
      std::true_type,
      typename elem<Elem, Seq<Tail...>>::type
    >::type
  ;
};




//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  foldl
//

template <template<typename , typename> class BinFunc, typename A, typename Seq>
struct foldl;


// Base Case: No more elements in the sequence.
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq
>
struct foldl<
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
struct foldl<
  BinaryFunc,
  CurVal,
  Seq<Val, Args...>
>
{
  using type = typename
    foldl<
      BinaryFunc,
      typename BinaryFunc<CurVal, Val>::type,
      Seq<Args...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  foldr
//

template <template<typename , typename> class BinFunc, typename A, typename Seq>
struct foldr;


// Base Case: No more elements in the sequence.
template <
  template <typename, typename> class BinaryFunc,
  typename CurVal,
  template <typename...> class Seq
>
struct foldr<
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
struct foldr<
  BinaryFunc,
  CurVal,
  Seq<Val, Args...>
>
{
  using type = typename
    BinaryFunc<
      Val,
      typename foldr<BinaryFunc, CurVal, Seq<Args...>>::type
    >::type
  ;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  fst
//

template <typename Pair>
struct fst;


template <
  template <typename...> class Pair,
  typename First,
  typename Second
>
struct fst<Pair<First, Second>>
{
  using type = First;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  head
//

template <typename Seq>
struct head;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct head<Seq<Head, Tail...>>
{
  using type = Head;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  id
//

template <typename T>
struct id;


template <typename T>
struct id
{
  using type = T;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  init
//

template <typename Seq>
struct init;


template <
  template <typename...> class Seq,
  typename... Args
>
struct init<Seq<Args...>>
{
  static_assert(
    sizeof...(Args) > 0,
    "Not enough args given to prelude::init!"
  );

  using type = typename
    take<
      std::integral_constant<std::size_t, sizeof...(Args) - 1>, Seq<Args...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  last
//

template <typename Seq>
struct last;


template <
  template <typename...> class Seq,
  typename... Args
>
struct last<Seq<Args...>>
{
  static_assert(
    sizeof...(Args) > 0,
    "Not enough args given to prelude::last!"
  );

  using type = typename
    at<
      Seq<Args...>,
      std::integral_constant<std::size_t, sizeof...(Args) - 1>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  length
//

template <typename Seq>
struct length;


template <
  template <typename...> class Seq,
  typename... Args
>
struct length<Seq<Args...>>
{
  using type = typename
    std::integral_constant<std::size_t, sizeof...(Args)>::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  map
//

template <template <typename> class Functor, typename Seq>
struct map;


template <
  template <typename> class Functor,
  typename Seq
>
struct map
{
  using type = typename detail::map_wetp<Functor,tlist<>,Seq>::type;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  negate
//

template <typename Number>
struct negate;


template <
  typename NumType,
  NumType value
>
struct negate<std::integral_constant<NumType, value>>
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
//  notElem
//

template <typename Elem, typename Seq>
struct notElem;


template <typename Elem, typename Seq>
struct notElem
{
  using type = typename not_<typename elem<Elem,Seq>::type>::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  not_
//

template <typename Constant>
struct not_;


template <>
struct not_<std::true_type>
{
  using type = typename std::false_type::type;
};

template <>
struct not_<std::false_type>
{
  using type = typename std::true_type::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  null
//

template <typename Seq>
struct null;


template <typename Seq>
struct null
{
  using type = std::true_type;
};

template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct null<Seq<Head,Tail...>>
{
  using type = std::false_type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  or_
//

template <typename Seq>
struct or_;


// Base case: No more elements meaning they must have all been false
template <typename Seq>
struct or_
{
  using type = typename std::false_type::type;
};

// Base case: True encountered, making the ``or" true
template <
  template <typename...> class Seq,
  typename... Tail
>
struct or_<Seq<std::true_type, Tail...>>
{
  using type =  typename std::true_type::type;
};

// Recursive case: False encountered, continue for the rest of the list
template <
  template <typename...> class Seq,
  typename... Tail
>
struct or_<Seq<std::false_type, Tail...>>
{
  using type = typename or_<Seq<Tail...>>::type;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  replicate
//

template <typename N, typename T>
struct replicate;


template <
  std::size_t N,
  typename T
>
struct replicate<std::integral_constant<std::size_t, N>, T>
{
  using type = typename
    detail::replicate_wetp<
      tlist<>, std::integral_constant<std::size_t, N>, T
    >::type
  ;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  reverse
//

template <typename Seq>
struct reverse;


template <
  template <typename...> class Seq,
  typename... Args
>
struct reverse<Seq<Args...>>
{
  using type = typename
    detail::reverse_wetp<
      Seq<>, Seq<Args...>
    >::type
  ;
};



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  tail
//

template <typename Seq>
struct tail;


template <
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct tail<Seq<Head, Tail...>>
{
  using type = typename tlist<Tail...>::type;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  take
//

template <typename N, typename Seq>
struct take;


template <
  typename SizeType,
  SizeType N,
  template <typename...> class Seq,
  typename Head,
  typename... Tail
>
struct take<std::integral_constant<SizeType, N>, Seq<Head, Tail...>>
{
  using type = typename
    detail::take_wetp<
      std::integral_constant<SizeType, N>, tlist<>, Seq<Head,Tail...>
    >::type
  ;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//  zip
//

template <typename SeqOne, typename SeqTwo>
struct zip;


template <
  template <typename...> class Seq1, typename... Args1,
  template <typename...> class Seq2, typename... Args2
>
struct zip<Seq1<Args1...>, Seq2<Args2...> >
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

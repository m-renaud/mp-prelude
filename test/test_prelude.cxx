#include "../include/prelude.hxx"
#include "../include/core.hxx"
#include "../include/demangle.hxx"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstddef>
#include <functional>
#include <type_traits>

using namespace mrr::mp::prelude;

using std::true_type;
using std::false_type;

using mrr::mp::tlist;

typedef std::integral_constant<std::size_t, 0> c_0;
typedef std::integral_constant<std::size_t, 1> c_1;
typedef std::integral_constant<std::size_t, 2> c_2;
typedef std::integral_constant<std::size_t, 3> c_3;
typedef std::integral_constant<std::size_t, 4> c_4;


typedef std::integral_constant<int, 0> i_0;
typedef std::integral_constant<int, 1> i_1;
typedef std::integral_constant<int, 2> i_2;
typedef std::integral_constant<int, 3> i_3;
typedef std::integral_constant<int, 4> i_4;

typedef std::integral_constant<int, -3> n_3;

template <typename T>
struct Display
{
  static void display(std::string const& label)
  {
    std::cout << std::left << std::setw(75)
              << label << " => "
              << demangled_name_of_type<T>()
              << std::endl
    ;
  }
};


int main()
{
  std::cout << "==================== all ====================\n";
  Display<all<std::is_arithmetic, tlist<int,long,double>>::type>::display(
    "all<std::is_arithmetic,tl<int,long,double>>::type"
  );

  Display<all<std::is_arithmetic, tlist<int,char*,double>>::type>::display(
    "all<std::is_arithmetic,tl<int,char*,double>>::type"
  );

  Display<all<std::is_const, tlist<int const,double const>>::type>::display(
    "all<std::is_const,tl<int const, double const>>::type"
  );


  std::cout << "\n==================== and_ ====================\n";
  Display<and_<tlist<c_1, true_type>>::type>::display(
    "and_<tl<true_type, true_type>>::type"
  );


  Display<and_<tlist<false_type, true_type>>::type>::display(
    "and_<tl<false_type, true_type>>::type"
  );


  std::cout << "\n==================== any ====================\n";
  Display<any<std::is_arithmetic, tlist<int,long,double>>::type>::display(
    "any<std::is_arithmetic,tl<int,long,double>>::type"
  );

  Display<any<std::is_arithmetic, tlist<int*,char*,double*>>::type>::display(
    "any<std::is_arithmetic,tl<int*,char*,double*>>::type"
  );

  Display<any<std::is_const, tlist<int const,double>>::type>::display(
    "any<std::is_const,tl<int const, double>>::type"
  );


  std::cout << "\n==================== at ====================\n";
  Display<at<tlist<int, double, char>, c_0>::type>::display(
    "at<tlist<int, double, char>, c_0>"
  );

  Display<at<tlist<int, double, char>, c_1>::type>::display(
    "at<tlist<int, double, char>, c_1>"
  );

  std::cout << "\n==================== concat ====================\n";
  Display<concat<tlist<int, double>, tlist<char, float>>::type>::display(
    "concat<tl<int, double>, tl<char, float>>"
  );


  std::cout << "\n==================== drop ====================\n";
  Display<drop<c_2, tlist<int,double,char,float>>::type>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );

  Display<drop<c_3, tlist<int,double,char,float>>::type>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );

  Display<drop<c_4, tlist<int,double,char,float>>::type>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );


  std::cout << "\n==================== elem ====================\n";
  Display<elem<c_1, tlist<c_0, c_1>>::type>::display(
    "elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 1>>"
  );

  Display<elem<c_1, tlist<c_0, c_2>>::type>::display(
    "elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 2>>"
  );

#if 0
  Display<elem<int, tlist<unsigned int, long, char>>::type>::display(
    "elem<int, tlist<unsigned int, long, char>>"
  );
#endif


  std::cout << "\n==================== foldl ====================\n";
  Display<foldl<mrr::mp::plus, i_0, tlist<i_4,i_2>>::type>::display(
    "foldl<add<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  Display<foldl<mrr::mp::minus, i_0, tlist<i_4,i_2>>::type>::display(
    "foldl<minus<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  std::cout << "\n==================== foldr ====================\n";
  Display<foldr<mrr::mp::multiplies, i_1, tlist<i_4,i_2>>::type>::display(
    "foldr<mul<int>, constant<int, 1>, tl<constant<int, 4>, constant<int, 2>>"
  );

  Display<foldr<mrr::mp::minus, i_0, tlist<i_4,i_2>>::type>::display(
    "foldr<add<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  std::cout << "\n==================== fst ====================\n";
  Display<fst<tlist<int, double>>::type>::display(
    "fst<tl<int, double>>"
  );


  std::cout << "\n==================== head ====================\n";
  Display<head<tlist<int, double, char, float>>::type>::display(
    "head<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== init ====================\n";
  Display<init<tlist<int, double, char, float>>::type>::display(
    "init<tl<int, double, char, float>>"
  );

#if 0   // Fails from static_assert as expected
  Display<init<tlist<>>::type>::display(
    "init<tl<int, double, char, float>>"
  );
#endif

  std::cout << "\n==================== last ====================\n";
  Display<last<tlist<int, double, char, float>>::type>::display(
    "last<tl<int, double, char, float>>"
  );

#if 0   // Fails from static_assert as expected
  Display<last<tlist<>>::type>::display(
    "last<tl<>>"
  );
#endif


  std::cout << "\n==================== length ====================\n";
  Display<length<tlist<int, double, char, float>>::type>::display(
    "length<tl<int, double, char, float>>"
  );

  Display<length<tlist<>>::type>::display(
    "length<tl<>>"
  );


  std::cout << "\n==================== map ====================\n";
  Display<map<std::make_unsigned, tlist<char, short, int>>::type>::display(
    "map<std::make_unsigned, tlist<char, short, int>>"
  );

  Display<map<std::is_arithmetic, tlist<int, std::ostream>>::type>::display(
    "map<std::is_arithmetic, tlist<int, std::ostream>>"
  );


  std::cout << "\n==================== negate ====================\n";
  Display<negate<c_3>::type>::display(
    "negate<c_3>"
  );

  Display<negate<n_3>::type>::display(
    "negate<n_3>"
  );


  std::cout << "\n==================== notElem ====================\n";
  Display<notElem<c_1, tlist<c_0, c_1>>::type>::display(
    "notElem<constant<int, 1>,tl<constant<int, 0>, constant<int, 1>>"
  );

  Display<notElem<c_1, tlist<c_0, c_2>>::type>::display(
    "notElem<constant<int, 1>,tl<constant<int, 0>, constant<int, 2>>"
  );


  std::cout << "\n==================== not_ ====================\n";
  Display<not_<true_type>::type>::display(
    "not_<true_type>"
  );

  Display<not_<false_type>::type>::display(
    "not_<false_type>"
  );


  std::cout << "\n==================== null ====================\n";
  Display<null<tlist<>>::type>::display(
    "null<tl<>>"
  );

  Display<null<tlist<int, double, char, float>>::type>::display(
    "null<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== or_ ====================\n";
  Display<or_<tlist<false_type, false_type>>::type>::display(
    "or_<tl<false_type, false_type>>"
  );

  Display<or_<tlist<true_type, false_type>>::type>::display(
    "or_<tl<true_type, false_type>>"
  );

//  << "product<tl<constant<int, 3>, constant<int, 4>>              =>  "
//  << demangled_name_of_type<product<tlist<constant<int,3>, constant<int, 4>>>::type>()
//  << std::endl


  std::cout << "\n==================== replicate ====================\n";
  Display<replicate<c_3, int>::type>::display(
    "replicate<c_3, int>"
  );


  std::cout << "\n==================== reverse ====================\n";
  Display<reverse<tlist<int, double, char, float>>::type>::display(
    "reverse<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== tail ====================\n";
  Display<tail<tlist<int, double, char, float>>::type>::display(
    "tail<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== take ====================\n";
  Display<take<c_3, tlist<int, double, char, float>>::type>::display(
    "take<c_3, tl<int, double, char, float>>"
  );


  std::cout << "\n==================== zip ====================\n";
  Display<zip<tlist<int, double>, tlist<char, float>>::type>::display(
    "zip<tl<int, double>, tl<char, float>>"
  );

}

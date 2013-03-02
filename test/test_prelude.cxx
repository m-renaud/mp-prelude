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
  Display<all<std::is_arithmetic, tlist<int,long,double>>>::display(
    "all<std::is_arithmetic,tl<int,long,double>>"
  );

  Display<all<std::is_arithmetic, tlist<int,char*,double>>>::display(
    "all<std::is_arithmetic,tl<int,char*,double>>"
  );

  Display<all<std::is_const, tlist<int const,double const>>>::display(
    "all<std::is_const,tl<int const, double const>>"
  );


  std::cout << "\n==================== and_ ====================\n";
  Display<and_<tlist<true_type, true_type>>>::display(
    "and_<tl<true_type, true_type>>"
  );


  Display<and_<tlist<false_type, true_type>>>::display(
    "and_<tl<false_type, true_type>>"
  );


  std::cout << "\n==================== any ====================\n";
  Display<any<std::is_arithmetic, tlist<int,long,double>>>::display(
    "any<std::is_arithmetic,tl<int,long,double>>"
  );

  Display<any<std::is_arithmetic, tlist<int*,char*,double*>>>::display(
    "any<std::is_arithmetic,tl<int*,char*,double*>>"
  );

  Display<any<std::is_const, tlist<int const,double>>>::display(
    "any<std::is_const,tl<int const, double>>"
  );


  std::cout << "\n==================== at ====================\n";
  Display<at<tlist<int, double, char>, c_0>>::display(
    "at<tlist<int, double, char>, c_0>"
  );

  Display<at<tlist<int, double, char>, c_1>>::display(
    "at<tlist<int, double, char>, c_1>"
  );

  std::cout << "\n==================== concat ====================\n";
  Display<concat<tlist<int, double>, tlist<char, float>>>::display(
    "concat<tl<int, double>, tl<char, float>>"
  );


  std::cout << "\n==================== drop ====================\n";
  Display<drop<c_2, tlist<int,double,char,float>>>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );

  Display<drop<c_3, tlist<int,double,char,float>>>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );

  Display<drop<c_4, tlist<int,double,char,float>>>::display(
    "drop<c_2, tl<int, double, char, float>>"
  );


  std::cout << "\n==================== elem ====================\n";
  Display<elem<c_1, tlist<c_0, c_1>>>::display(
    "elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 1>>"
  );

  Display<elem<c_1, tlist<c_0, c_2>>>::display(
    "elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 2>>"
  );

#if 0
  Display<elem<int, tlist<unsigned int, long, char>>>::display(
    "elem<int, tlist<unsigned int, long, char>>"
  );
#endif


  std::cout << "\n==================== foldl ====================\n";
  Display<foldl<mrr::mp::plus, i_0, tlist<i_4,i_2>>>::display(
    "foldl<add<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  Display<foldl<mrr::mp::minus, i_0, tlist<i_4,i_2>>>::display(
    "foldl<minus<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  std::cout << "\n==================== foldr ====================\n";
  Display<foldr<mrr::mp::multiplies, i_1, tlist<i_4,i_2>>>::display(
    "foldr<mul<int>, constant<int, 1>, tl<constant<int, 4>, constant<int, 2>>"
  );

  Display<foldr<mrr::mp::minus, i_0, tlist<i_4,i_2>>>::display(
    "foldr<add<int>, constant<int, 0>, tl<constant<int, 4>, constant<int, 2>>"
  );

  std::cout << "\n==================== fst ====================\n";
  Display<fst<tlist<int, double>>>::display(
    "fst<tl<int, double>>"
  );


  std::cout << "\n==================== head ====================\n";
  Display<head<tlist<int, double, char, float>>>::display(
    "head<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== init ====================\n";
  Display<init<tlist<int, double, char, float>>>::display(
    "init<tl<int, double, char, float>>"
  );

#if 0   // Fails from static_assert as expected
  Display<init<tlist<>>>::display(
    "init<tl<int, double, char, float>>"
  );
#endif

  std::cout << "\n==================== last ====================\n";
  Display<last<tlist<int, double, char, float>>>::display(
    "last<tl<int, double, char, float>>"
  );

#if 0   // Fails from static_assert as expected
  Display<last<tlist<>>>::display(
    "last<tl<>>"
  );
#endif


  std::cout << "\n==================== length ====================\n";
  Display<length<tlist<int, double, char, float>>>::display(
    "length<tl<int, double, char, float>>"
  );

  Display<length<tlist<>>>::display(
    "length<tl<>>"
  );


  std::cout << "\n==================== map ====================\n";
  Display<map<std::make_unsigned, tlist<char, short, int>>>::display(
    "map<std::make_unsigned, tlist<char, short, int>>"
  );

  Display<map<std::is_arithmetic, tlist<int, std::ostream>>>::display(
    "map<std::is_arithmetic, tlist<int, std::ostream>>"
  );


  std::cout << "\n==================== negate ====================\n";
  Display<negate<c_3>>::display(
    "negate<c_3>"
  );

  Display<negate<n_3>>::display(
    "negate<n_3>"
  );


  std::cout << "\n==================== notElem ====================\n";
  Display<not_elem<c_1, tlist<c_0, c_1>>>::display(
    "not_elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 1>>"
  );

  Display<not_elem<c_1, tlist<c_0, c_2>>>::display(
    "not_elem<constant<int, 1>,tl<constant<int, 0>, constant<int, 2>>"
  );


  std::cout << "\n==================== not_ ====================\n";
  Display<not_<true_type>>::display(
    "not_<true_type>"
  );

  Display<not_<false_type>>::display(
    "not_<false_type>"
  );


  std::cout << "\n==================== null ====================\n";
  Display<null<tlist<>>>::display(
    "null<tl<>>"
  );

  Display<null<tlist<int, double, char, float>>>::display(
    "null<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== or_ ====================\n";
  Display<or_<tlist<false_type, false_type>>>::display(
    "or_<tl<false_type, false_type>>"
  );

  Display<or_<tlist<true_type, false_type>>>::display(
    "or_<tl<true_type, false_type>>"
  );

//  << "product<tl<constant<int, 3>, constant<int, 4>>              =>  "
//  << demangled_name_of_type<product<tlist<constant<int,3>, constant<int, 4>>>>()
//  << std::endl


  std::cout << "\n==================== replicate ====================\n";
  Display<replicate<c_3, int>>::display(
    "replicate<c_3, int>"
  );


  std::cout << "\n==================== reverse ====================\n";
  Display<reverse<tlist<int, double, char, float>>>::display(
    "reverse<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== tail ====================\n";
  Display<tail<tlist<int, double, char, float>>>::display(
    "tail<tl<int, double, char, float>>"
  );


  std::cout << "\n==================== take ====================\n";
  Display<take<c_3, tlist<int, double, char, float>>>::display(
    "take<c_3, tl<int, double, char, float>>"
  );


  std::cout << "\n==================== zip ====================\n";
  Display<zip<tlist<int, double>, tlist<char, float>>>::display(
    "zip<tl<int, double>, tl<char, float>>"
  );

}

#include <typeinfo>
#include <string>
#include <cxxabi.h>   // GCC-specific

template <typename T>
std::string demangled_name_of_type()
{
  // NOTE: See GCC Manual Chapter 27.
  //       http://gcc.gnu.org/onlinedocs/libstdc++/
  int status;
  char *name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
  std::string realname(name);
  free(name);
  return realname;
}

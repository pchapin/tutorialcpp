
#include <limits.h>

#ifdef NEVER
#define CREATE_INT_TYPE(name, upper)      \
  #if upper < SHRT_MAX                    \
    typedef short name;                   \
  #elif upper < INT_MAX                   \
    typedef int name;                     \
  #elif upper < LONG_MAX                  \
    typedef long name;                    \
  #elif upper < LLONG_MAX                 \
    typedef long long name;               \
  #else                                   \
    #error Unable to define suitable type \
  #endif
#endif

#define typename

template<long long x, long long y>
struct is_below {
  enum { value = ( x < y ) };
};

template<int flag>
struct create_int_type { };

// template<>
struct create_int_type<1> {
  typedef short type;
};

// template<>
struct create_int_type<2> {
  typedef int type;
};

// template<>
struct create_int_type<3> {
  typedef long type;
};

// template<>
struct create_int_type<4> {
  typedef long long type;
};

template<long long upper>
struct select_int {
  typedef typename create_int_type<
    (is_below<upper, SHRT_MAX>::value == 1 ? 1 :
      (is_below<upper, INT_MAX>::value == 1 ? 2 :
        (is_below<upper, LONG_MAX>::value == 1 ? 3 : 4)))>::type type;
};


#ifdef NEVER

// Sample usage.

#include <iostream>
#include "integer.h"

#define MAX 100000000000

typedef select_int<MAX>::type counter_t;

int main(void)
{
  counter_t counter = MAX;

  std::cout << counter << std::endl;
  return 0;
}
#endif



#include "cloak.h"

CHECK(PROBE(~)) // Expands to 1
CHECK(xxx) // Expands to 0

#define M(i, _) i
EVAL(REPEAT(8, M, ~)) // 0 1 2 3 4 5 6 7
#undef M

#define A(i, id) \
COMMA_IF(i) \
template<REPEAT(INC(i), B, ~)> class id ## i \
/**/
#define B(i, _) COMMA_IF(i) class


EVAL(REPEAT(3, A, T))
//template< class> class T0 , template< class , class> class T1 , template< class , class , class> class T2

#undef A
#undef B

#define PRED(state, ...) BOOL(state)
#define OP(state, ...) DEC(state), state, __VA_ARGS__
#define MACRO(state) state

EVAL(WHILE(PRED, OP, 8,)) // 0, 1, 2, 3, 4, 5, 6, 7, 8,

#undef PRED
#undef OP
#undef MACRO

#define COMPARE_foo(x) x
#define COMPARE_bar(x) x

PRIMITIVE_COMPARE(foo, bar) // Expands to 1
PRIMITIVE_COMPARE(foo, foo) // Expands to 0

NOT_EQUAL(foo, bar) // Expands to 1
NOT_EQUAL(foo, foo) // Expands to 0
NOT_EQUAL(foo, unfoo) // Expands to 1

EQUAL(foo, bar) // Expands to 0
EQUAL(foo, foo) // Expands to 1
EQUAL(foo, unfoo) // Expands to 0

#undef COMPARE_foo
#undef COMPARE_bar

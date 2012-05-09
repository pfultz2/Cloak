

#define M(s, i, _) i
EXPR_S(0)(REPEAT_S(0, 8, M, ~)) // 0 1 2 3 4 5 6 7


#define A(s, i, id) \
COMMA_IF(i) \
template<EXPR_S(s)(REPEAT_S(s, INC(i), B, ~))> class id ## i \
/**/
#define B(s, i, _) COMMA_IF(i) class

EXPR_S(0)(REPEAT_S(0, 3, A, T))
//template< class> class T0 , template< class , class> class T1 , template< class , class , class> class T2

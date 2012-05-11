

#include "cloak.h"


#define M(s, i, _) i
EXPR_S(0)(REPEAT_S(0, 8, M, ~)) // 0 1 2 3 4 5 6 7



#define A(s, i, id) \
COMMA_IF(i) \
template<EXPR_S(s)(REPEAT_S(s, INC(i), B, ~))> class id ## i \
/**/
#define B(s, i, _) COMMA_IF(i) class


EXPR_S(0)(REPEAT_S(0, 3, A, T))
//template< class> class T0 , template< class , class> class T1 , template< class , class , class> class T2

#define C(s, n, _) n
EXPR_S(0)(REPEAT_S(0, 7, C, ~))

#define FOR_S(s, pred, op, macro, ...) \
    FOR_I(OBSTRUCT(), INC(s), pred, op, macro, __VA_ARGS__) \
    /**/
#define FOR_INDIRECT() FOR_I
#define FOR_I(_, s, pred, op, macro, ...) \
    WHEN _(pred _(s, __VA_ARGS__))( \
        macro _(s, __VA_ARGS__) \
        EXPR_S(s) _(FOR_INDIRECT _()( \
            OBSTRUCT _(), INC(s), \
            pred, op, macro, op _(s, __VA_ARGS__) \
        )) \
    ) \
    /**/
    
    
#define PRED(s, state) BOOL(state)
#define OP(s, state) DEC(state)
#define MACRO(s, state) state

EXPR_S(0)(FOR_S(0, PRED, OP, MACRO, 8)) // 8 7 6 5 4 3 2 1



#define WHILE_S(s, pred, op, ...) \
    WHILE_I(OBSTRUCT(), INC(s), pred, op, __VA_ARGS__)
    
#define WHILE_INDIRECT() WHILE_I
#define WHILE_I(_, s, pred, op, ...) \
    WHEN _(pred _(s, __VA_ARGS__)) \
    ( \
        __VA_ARGS__ \
        EXPR_S(s) _ \
        ( \
            WHILE_INDIRECT _()(OBSTRUCT _(), INC(s), pred, op, op _(s, __VA_ARGS__) ) \
        ) \
    )

EXPR_S(0)(WHILE_S(0, PRED, OP, 8)) // 8 7 6 5 4 3 2 1



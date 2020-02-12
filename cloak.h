/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    cloak.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef CLOAK_GUARD_H
#define CLOAK_GUARD_H

/* fix bug: In Visual Stido, __VA_ARGS__ is treated as a separate parameter */
#define FIX_VS_BUG(x) x

/* catenate */
#define PRIMITIVE_CAT(a, ...) FIX_VS_BUG(a ## __VA_ARGS__)
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)

/* unary complement (bit inversion) */
#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

/* BITAND(x)(y) => x & y */
#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

/* increase */
#define INC(x) PRIMITIVE_CAT(INC_, x)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 9
/* ... */

/* decrease */
#define DEC(x) PRIMITIVE_CAT(DEC_, x)
#define DEC_0 0
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
/* ... */

/* run the 2nd param */
#define CHECK_N(x, n, ...) n
#define CHECK(...) FIX_VS_BUG(CHECK_N(__VA_ARGS__, 0,))
#define PROBE(x) x, 1,

/* PROBE(~) => ~, 1, */
#define IS_PAREN_PROBE(...) PROBE(~)
/* IS_PAREN(xxx) => 0 */
/* IS_PAREN((xxx)) => 1 */
#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
/* run the 2nd param */
#define IIF_0(t, ...) __VA_ARGS__
/* run the 1st param */
#define IIF_1(t, ...) t

#define IF(c) IIF(BOOL(c))

#define EAT(...)
#define EXPAND(...) __VA_ARGS__
/* WHEN(0)(...) => EXPAND(...) => ... */
/* WHEN(1)(...) => EAT(...) => *nothing* */
#define WHEN(c) IF(c)(EXPAND, EAT)

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(id) id DEFER(EMPTY)()

/* evaluate? */
#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

/* EVAL(REPEAT(3, A, B)) => A(0, B) A(1, B) A(2, B) */
#define REPEAT(count, macro, ...) \
    WHEN(count) ( \
        OBSTRUCT(REPEAT_INDIRECT) () ( \
            DEC(count), macro, __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT

/*
    EVAL(WHILE(A, B, C)) =>
    while (A(C)) {
        C = B(C).args[0];
        // DARK MAGIC ~
    }
    return args;
*/
#define WHILE(pred, op, ...) \
    IF(pred(__VA_ARGS__)) ( \
        OBSTRUCT(WHILE_INDIRECT) () ( \
            pred, op, op(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
    )
#define WHILE_INDIRECT() WHILE

/*
    #define COMPARE_foo(x) x
    #define COMPARE_bar(x) x
    PRIMITIVE_COMPARE(foo, bar) // Expands to 1
    PRIMITIVE_COMPARE(foo, foo) // Expands to 0
*/
#define PRIMITIVE_COMPARE(x, y) IS_PAREN ( \
    COMPARE_ ## x ( COMPARE_ ## y) (()) \
)

#define IS_COMPARABLE(x) IS_PAREN( CAT(COMPARE_, x) (()) )

#define NOT_EQUAL(x, y) \
IIF(BITAND(IS_COMPARABLE(x))(IS_COMPARABLE(y))) ( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)

#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))

#define COMMA() ,

#define COMMA_IF(n) IF(n)(COMMA, EAT)()

#endif
